package com.zego.livedemo5.ui.activities.wolvesgame;

import android.Manifest;
import android.app.Activity;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Message;
import android.provider.Settings;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.text.TextUtils;
import android.view.View;
import android.widget.Toast;

import com.zego.livedemo5.R;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.presenters.RoomInfo;
import com.zego.livedemo5.utils.JsonUtil;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.zegoliveroom.callback.IZegoCustomCommandCallback;
import com.zego.zegoliveroom.callback.IZegoLivePlayerCallback;
import com.zego.zegoliveroom.callback.IZegoLivePublisherCallback;
import com.zego.zegoliveroom.callback.IZegoLoginCompletionCallback;
import com.zego.zegoliveroom.callback.IZegoRoomCallback;
import com.zego.zegoliveroom.callback.im.IZegoIMCallback;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.constants.ZegoIM;
import com.zego.zegoliveroom.constants.ZegoVideoViewMode;
import com.zego.zegoliveroom.entity.AuxData;
import com.zego.zegoliveroom.entity.ZegoBigRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamQuality;
import com.zego.zegoliveroom.entity.ZegoConversationMessage;
import com.zego.zegoliveroom.entity.ZegoRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;
import com.zego.zegoliveroom.entity.ZegoUser;
import com.zego.zegoliveroom.entity.ZegoUserState;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.HashMap;

import butterknife.OnClick;

public class WolvesGameInTurnActivity extends WolvesGameBaseActivity {
    private String anchorId;
    private String anchorName;

    /** true: 不能参与游戏，只能作为观众，如人数超过上限； false: 能参与游戏 */
    private boolean onlyAudienceRole = false;

    /** 登录房间之前就有的流，在得到房间信息后需要播放出来 */
    private ZegoStreamInfo[] beforeLoginStreamList;

    public static void actionStart(Activity context, RoomInfo roomInfo)  {
        Intent intent = new Intent(context, WolvesGameInTurnActivity.class);
        intent.putExtra(IntentExtra.ROOM_ID, roomInfo.room_id);
        intent.putExtra(IntentExtra.ROOM_NAME, roomInfo.room_name);
        intent.putExtra(IntentExtra.ANCHOR_ID, roomInfo.anchor_id_name);
        intent.putExtra(IntentExtra.ANCHOR_NAME, roomInfo.anchor_nick_name);
        context.startActivity(intent);
        context.overridePendingTransition(R.anim.scale_translate,
                R.anim.my_alpha_action);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();

        zegoLiveRoom.setZegoLivePublisherCallback(null);
        zegoLiveRoom.setZegoLivePlayerCallback(null);
        zegoLiveRoom.setZegoRoomCallback(null);
        zegoLiveRoom.setZegoIMCallback(null);

        if (hasLoginRoom) {
            zegoLiveRoom.logoutRoom();
        }

        mHandler.removeCallbacksAndMessages(null);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode) {
            case 101: {
                boolean openSettingActivity = false;
                if (grantResults[0] == PackageManager.PERMISSION_DENIED) {
                    Toast.makeText(this, R.string.allow_camera_permission, Toast.LENGTH_LONG).show();
                    openSettingActivity = true;
                }
                if (grantResults[1] == PackageManager.PERMISSION_DENIED) {
                    Toast.makeText(this, R.string.open_recorder_permission, Toast.LENGTH_LONG).show();
                    openSettingActivity = true;
                }

                if (openSettingActivity) {
                    Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
                    intent.setData(Uri.parse("package:" + getPackageName()));
                    startActivity(intent);
                } else {
                    startTalking();
                }
            }
                break;
            default:
                super.onRequestPermissionsResult(requestCode, permissions, grantResults);
                break;
        }
    }

    private boolean requestPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED
                    || ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, new String[]{
                        Manifest.permission.CAMERA, Manifest.permission.RECORD_AUDIO}, 101);
                return true;
            }
        }
        return false;
    }

    /**
     * 初始化从外部传递过来的数据.
     */
    @Override
    protected void initExtraData(Bundle savedInstanceState) {
        if (savedInstanceState == null) {
            Intent intent = getIntent();
            roomId = intent.getStringExtra(IntentExtra.ROOM_ID);
            roomName = intent.getStringExtra(IntentExtra.ROOM_NAME);
            anchorId = intent.getStringExtra(IntentExtra.ANCHOR_ID);
            anchorName = intent.getStringExtra(IntentExtra.ANCHOR_NAME);
        }
    }

    @Override
    protected void initViews(Bundle savedInstanceState) {
        super.initViews(savedInstanceState);
        mInTurnSpeaking.setVisibility(View.GONE);
        mEndInTurnSpeaking.setVisibility(View.GONE);
    }

    /**
     * 加载数据.
     */
    @Override
    protected void doBusiness(Bundle savedInstanceState) {
        zegoLiveRoom.setZegoRoomCallback(new ZegoRoomCallback());
        zegoLiveRoom.setZegoLivePublisherCallback(new ZegoLivePublisherCallback());
        zegoLiveRoom.setZegoLivePlayerCallback(new ZegoLivePlayerCallback());
        zegoLiveRoom.setZegoIMCallback(new ZegoIMCallback());

        loginChatRoom();
    }

    @OnClick(R.id.btn_start_or_stop_speaking)
    public void onStartOrStopSpeakingClick(View view) {
        if (isSpeaking) {
            stopTalking(true);
        } else {
            if (!requestPermission()) {
                startTalking();
            }
        }
    }

    /**
     * @see WolvesGameBaseActivity#handleUIMessage(Message)
     *
     * @param msg
     * @return
     */
    @Override
    protected boolean handleUIMessage(Message msg) {
        switch (msg.what) {
            case MsgIds.STOP_SPEAKING_FOR_ME:
                mTimerView.setVisibility(View.INVISIBLE);
                stopTalking(true);
                return true;

            default:
                return super.handleUIMessage(msg);
        }
    }

    private void sendStopSpeakingCommand() {
        JSONObject json = new JSONObject();
        try {
            json.put(kSpeakingCommandKey, SpeakingCmd.StopSpeaking);
            json.put(kSpeakingUserIdKey, PreferenceUtil.getInstance().getUserID());
        } catch (JSONException e) {
        }

        zegoLiveRoom.sendCustomCommand(getCurrentMembers(), json.toString(), new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("结束说话, errorCode: %d", errorCode);
            }
        });
    }

    /**
     * 停止说话
     *
     * @param sendNotify true: 需要发送 StopSpeaking 指令给Host（仅主动停止说话的情景下才需要，如果是接收来自于Host发送的停止指令，则不应该再发送 StopSpeaking 通知）; false: 不发送
     */
    private void stopTalking(boolean sendNotify) {
        isSpeaking = false;
        mBtnSpeaking.setText(R.string.start_speaking);

        mHandler.removeMessages(MsgIds.STOP_SPEAKING_FOR_ME);
        mHandler.removeMessages(MsgIds.UPDATE_COUNT_TIMER);
        if (currentSpeakingMode == SpeakingMode.FreeSpeakingMode) {
            mTextTips.setText(R.string.mode_free_speaking);
        } else if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
            mTextTips.setText(R.string.mode_in_turn_speaking);
            mBtnSpeaking.setEnabled(false);
            mTimerView.setVisibility(View.INVISIBLE);
        }

        zegoLiveRoom.stopPreview();
        zegoLiveRoom.setPreviewView(null);
        zegoLiveRoom.enableMic(false);
        zegoLiveRoom.enableCamera(false);
        if (currentPublishMode != PublishMode.Super_Low_Delay) {
            zegoLiveRoom.stopPublishing();
        }

        unBindStreamFromSpeakingHeaderViewAndHide();

        WolfInfo myInfo = getMyInfo();
        if (myInfo != null) {
            myInfo.setState(WolfInfo.SpeakingState.isIdle);
            mRecyclerAdapter.updateItem(myInfo);
        }

        if (sendNotify) {
            sendStopSpeakingCommand();
        }
    }

    private void loginChatRoom() {
        zegoLiveRoom.setRoomConfig(false, true);
        zegoLiveRoom.loginRoom(roomId, ZegoConstants.RoomRole.Audience, new IZegoLoginCompletionCallback() {
            @Override
            public void onLoginCompletion(int errorCode, ZegoStreamInfo[] zegoStreamInfos) {
                if (isFinishing()) return;

                if (errorCode == 0) {
                    recordLog("登录成功, roomId: %s", roomId);
                    hasLoginRoom = true;
                    mTextTips.setText(R.string.tips_login_success);
                    beforeLoginStreamList = zegoStreamInfos;
                    sendAskAnchorRoomInfoCommand();
                } else {
                    mTextTips.setText(R.string.tips_login_failed);
                    recordLog("登录房间失败，errorCode: %d", errorCode);

                    if (errorCode == 1048680) { // 主播离开房间
                        notifyAnchorLogout();
                    }
                }
            }
        });
    }

    /**
     * 请求房间信息，等待 {@link ZegoRoomCallback#onRecvCustomCommand(String, String, String, String)}
     */
    private void sendAskAnchorRoomInfoCommand() {
        mTextTips.setText(R.string.tips_wait_anchor_answer);

        JSONObject jsonObject = new JSONObject();
        try {
            jsonObject.put(kSpeakingCommandKey, SpeakingCmd.AskRoomInfo);
        } catch (JSONException e) {

        }

        ZegoUser anchor = new ZegoUser();
        anchor.userID = anchorId;
        anchor.userName = anchorName;

        zegoLiveRoom.sendCustomCommand(new ZegoUser[]{anchor}, jsonObject.toString(), new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("向主持人获取房间信息, errorCode: %d", errorCode);
            }
        });
    }

    private void notifyAnchorLogout() {
        AlertDialog.Builder dialogBuilder = new AlertDialog.Builder(this);
        dialogBuilder.setTitle(R.string.hint)
                .setMessage(R.string.dialog_anchor_leave_room)
                .setNegativeButton(R.string.got_it, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        onBackPressed();
                    }
                });
        dialogBuilder.create().show();
    }

    private String getOldStreamIdByUserId(String userId) {
        if (beforeLoginStreamList == null || beforeLoginStreamList.length == 0) return null;

        for (ZegoStreamInfo stream : beforeLoginStreamList) {
            if (TextUtils.equals(stream.userID, userId)) {
                return stream.streamID;
            }
        }
        return null;
    }

    private void handleAnswerRoomInfoCommand(JSONObject answerJson) {
        currentSpeakingMode = answerJson.optInt(kSpeakingModeKey, 0);
        boolean isUltraServer = answerJson.optBoolean(kServerModeIndexKey, false);
        currentPublishMode = isUltraServer ? PublishMode.Low_Delay : PublishMode.Low_Cost;

        boolean useSuperLowDelayMode = answerJson.optBoolean(kSuperLowDelayMode, false);
        if (useSuperLowDelayMode) {
            currentPublishMode = PublishMode.Super_Low_Delay;
        }
        mRecyclerAdapter.setSpeakingModeAndPublishMode(currentSpeakingMode, currentPublishMode);

        recordLog("主持人同意了你的请求，use publish mode: %s", currentPublishMode);

        JSONArray jsonUserList = answerJson.optJSONArray(kCurrentUserListKey);
        if (jsonUserList == null || jsonUserList.length() == 0) return;

        WolfInfo currentSpeakingUser = null;
        int currentUserCount = jsonUserList.length();
        for (int i = 0; i < currentUserCount; i++) {
            JSONObject jsonObject = jsonUserList.optJSONObject(i);
            WolfInfo wolf = decodeWolfInfo(jsonObject);
            if (wolf == null) continue;

            String streamId = getOldStreamIdByUserId(wolf.getUserId());
            if (!TextUtils.isEmpty(streamId)) {
                wolf.setStreamId(streamId);
            }
            allWolfMembers.add(wolf);

            if (wolf.getState() == WolfInfo.SpeakingState.isSpeaking) {
                currentSpeakingUser = wolf;
            }
        }

        int myIndex = answerJson.optInt(kUserIndexKey, 0);
        WolfInfo myInfo = new WolfInfo(PreferenceUtil.getInstance().getUserID(), PreferenceUtil.getInstance().getUserName());
        myInfo.setIndex(myIndex);
        allWolfMembers.add(myInfo);

        if (myIndex > 1) {
            if (currentSpeakingMode == SpeakingMode.FreeSpeakingMode) {    // 自由说话
                mTextTips.setText(R.string.mode_free_speaking);
                mBtnSpeaking.setEnabled(true);
            } else if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {   // 正在游戏，等待下一局
                mTextTips.setText(R.string.mode_in_turn_speaking_wait);
                mBtnSpeaking.setEnabled(false);

                if (currentSpeakingUser != null) {
                    mCurrentSpeakingHead.setVisibility(View.VISIBLE);
                    zegoLiveRoom.setViewMode(ZegoVideoViewMode.ScaleAspectFill, currentSpeakingUser.getStreamId());
                    zegoLiveRoom.startPlayingStream(currentSpeakingUser.getStreamId(), mCurrentSpeakingHead);
                }
            }
            mBtnSpeaking.setText(R.string.start_speaking);

            mRecyclerAdapter.updateData(allWolfMembers);

            int maxStreamCount = zegoLiveRoom.getMaxPlayChannelCount();
            if (currentUserCount >= maxStreamCount) {
                onlyAudienceRole = true;
                mTextTips.setText(R.string.tips_over_max_play_channle_count);
            } else {
                String streamId = publishWithoutPreview(roomName);
                myInfo.setStreamId(streamId);
            }
        } else {
            recordLog("主持人返回的座位号（%d）错误", myIndex);
        }

    }

    private void handleAllowSpeakingCommand(JSONObject json) {
        String userId = json.optString(kUserIdKey);
        if (TextUtils.isEmpty(userId)) return;

        // 轮到自己说话
        if (isMe(userId)) {
            mBtnSpeaking.setEnabled(true);
            mBtnSpeaking.setText(R.string.start_speaking);

            Message updateMsg = Message.obtain(mHandler, MsgIds.UPDATE_COUNT_TIMER, kSpeakingTimerInterval, 0);
            updateMsg.sendToTarget();

            mHandler.sendEmptyMessageDelayed(MsgIds.STOP_SPEAKING_FOR_ME, kSpeakingTimerInterval * 1000); // 60s后不论有没有开始说话，都必须停止说话
        }

        WolfInfo wolf = getWolfById(userId);
        wolf.setState(WolfInfo.SpeakingState.allowSpeaking);
        mRecyclerAdapter.updateItem(wolf);
    }

    private void handleStopSpeakingCommand(JSONObject json) {
        String userId = json.optString(kUserIdKey);
        if (isSpeaking && isMe(userId)) {
            stopTalking(false);
        } else {
            WolfInfo wolf = getWolfById(userId);
            if (wolf == null) return;

            zegoLiveRoom.stopPlayingStream(wolf.getStreamId());

            if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
                unBindStreamFromSpeakingHeaderViewAndHide();
            }

            wolf.setState(WolfInfo.SpeakingState.isIdle);
            mRecyclerAdapter.updateItem(wolf);
        }
    }

    private void handleNewUserJoinRoomCommand(JSONObject json) {
        JSONObject newUserJson = json.optJSONObject(kNewUserKey);
        if (newUserJson != null) {
            String userId = newUserJson.optString(kUserIdKey);
            String userName = newUserJson.optString(kUserNameKey);
            int index = newUserJson.optInt(kUserIndexKey);
            WolfInfo newWolf = new WolfInfo(userId, userName);
            newWolf.setIndex(index);
            allWolfMembers.add(newWolf);
//            mRecyclerAdapter.updateData(allWolfMembers, true);
            mRecyclerAdapter.insertItem(newWolf);
        }

    }

    private boolean removeMemberById(String userId) {
        boolean foundWolf = false;
        for (WolfInfo wolf : allWolfMembers) {
            if (userId.equals(wolf.getUserId())) {
                foundWolf = true;
                allWolfMembers.remove(wolf);
//                mRecyclerAdapter.deleteItem(wolf);
                break;
            }
        }

        if (foundWolf) {
            mRecyclerAdapter.updateData(allWolfMembers);
        }

        return foundWolf;
    }

    private void handleUserLeaveRoomCommand(JSONObject json) {
        String userId = json.optString(kUserIdKey);
        if (TextUtils.isEmpty(userId)) return;

        removeMemberById(userId);
    }

    private void stopCurrentMode() {
        for (WolfInfo wolf : allWolfMembers) {
            if (wolf == null || TextUtils.isEmpty(wolf.getStreamId())) continue;

            if (isMe(wolf.getUserId())) {
                isSpeaking = false;
                zegoLiveRoom.stopPreview();
                zegoLiveRoom.setPreviewView(null);
                zegoLiveRoom.enableMic(false);
                zegoLiveRoom.enableCamera(false);
                if (currentPublishMode != PublishMode.Super_Low_Delay) {
                    zegoLiveRoom.stopPublishing();
                }
            } else {
                zegoLiveRoom.stopPlayingStream(wolf.getStreamId());
            }
            wolf.setState(WolfInfo.SpeakingState.isIdle);
            if (currentPublishMode != PublishMode.Super_Low_Delay) {
                wolf.setStreamId(null);
            }
            mRecyclerAdapter.updateItem(wolf);
        }
    }

    private void handleInTurnSpeakingCommand(JSONObject json) {
        currentSpeakingMode = SpeakingMode.InTurnSpeakingMode;
        mTextTips.setText(R.string.mode_in_turn_speaking);
        mBtnSpeaking.setEnabled(false);

        JSONObject wolfCharacters = json.optJSONObject(kUserCharacterKey);
        if (wolfCharacters != null) {
            String myId = PreferenceUtil.getInstance().getUserID();
            int myCharacter = wolfCharacters.optInt(myId);
            mTextRole.setText(getString(R.string.wolf_role, myCharacter));
            mTextRole.setVisibility(View.VISIBLE);
        }

        mRecyclerAdapter.setSpeakingModeAndPublishMode(SpeakingMode.InTurnSpeakingMode, currentPublishMode);

        stopCurrentMode();
    }

    private void handleFreeSpeakingCommand(JSONObject json) {
        mHandler.removeCallbacksAndMessages(null);
        mTimerView.setVisibility(View.INVISIBLE);

        currentSpeakingMode = SpeakingMode.FreeSpeakingMode;
        mTextTips.setText(R.string.mode_free_speaking);

        mBtnSpeaking.setText(R.string.start_speaking);
        mBtnSpeaking.setEnabled(true);

        mTextRole.setVisibility(View.INVISIBLE);
        mCurrentSpeakingHead.setVisibility(View.GONE);

        mRecyclerAdapter.setSpeakingModeAndPublishMode(SpeakingMode.FreeSpeakingMode, currentPublishMode);

        stopCurrentMode();
    }

    //============ call back delegates ===============//
    private class ZegoLivePublisherCallback implements IZegoLivePublisherCallback {
        /**
         * 推流状态更新.
         *
         * @param stateCode     状态码, 0:成功, 其它:失败
         * @param streamId      流ID
         * @param streamInfo    推流信息
         */
        @Override
        public void onPublishStateUpdate(int stateCode, String streamId, HashMap<String, Object> streamInfo) {
            recordLog("推流状态更新, stateCode: %d; streamId: %s; Stream: %s", stateCode, streamId, streamInfo);
            if (stateCode == 0) {
                if (dontPreviewWhenPublishSuccess) {
                    dontPreviewWhenPublishSuccess = false;
                    return;
                }

                WolfInfo myInfo = getMyInfo();
                if (myInfo == null) return;

                myInfo.setState(WolfInfo.SpeakingState.isSpeaking);
                myInfo.setStreamId(streamId);
                mRecyclerAdapter.updateItem(myInfo);

                mTextTips.setText(R.string.mode_update_system_success);

                if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
                    bindStream2SpeakingHeaderViewAndShow(streamId);

                    zegoLiveRoom.setPreviewView(mCurrentSpeakingHead);
                    zegoLiveRoom.setPreviewViewMode(ZegoVideoViewMode.ScaleAspectFill);
                    zegoLiveRoom.startPreview();
                }
            }
        }

        /**
         * 收到连麦请求.
         *
         * @param seq            请求seq
         * @param fromUserId     来源用户ID
         * @param fromUserName   来源用户名
         * @param roomId         房间ID
         */
        @Override
        public void onJoinLiveRequest(int seq, String fromUserId, String fromUserName, String roomId) {
            recordLog("收到连麦请求, seq: %d; roomId: %s; fromUserId: %s; fromUserName: %s", seq, roomId, fromUserId, fromUserName);
        }

        @Override
        public void onPublishQualityUpdate(String s, ZegoStreamQuality streamQuality) {

        }

        /**
         * 音乐伴奏回调, 每次取20毫秒的数据.
         *
         * @param dataLen  20毫秒的数据长度
         * @return 背景音乐数据
         */
        @Override
        public AuxData onAuxCallback(int dataLen) {
            return null;
        }

        /**
         * 采集视频的宽度和高度变化通知.
         *
         * @param width     视频宽度
         * @param height    视频高度
         */
        @Override
        public void onCaptureVideoSizeChangedTo(int width, int height) {

        }

        /**
         * 混流配置更新。
         *
         * @param stateCode     状态码, 0:成功, 其它:失败
         * @param mixStreamId   混流ID
         * @param streamInfo    混流信息
         */
        @Override
        public void onMixStreamConfigUpdate(int stateCode, String mixStreamId, HashMap<String, Object> streamInfo) {

        }
    }

    private class ZegoLivePlayerCallback implements IZegoLivePlayerCallback {
        /**
         * 拉流状态更新.
         *
         * @param stateCode     状态码, 0:成功, 其它:失败
         * @param streamId      流ID
         */
        @Override
        public void onPlayStateUpdate(int stateCode, String streamId) {
            recordLog("拉流状态更新, stateCode: %d; streamId: %s", stateCode, streamId);
        }

        @Override
        public void onPlayQualityUpdate(String s, ZegoStreamQuality streamQuality) {

        }

        @Override
        public void onRecvEndJoinLiveCommand(String fromUserId, String fromUserName, String roomId) {
        }

        /**
         * 收到连麦邀请.
         *
         * @param seq           请求 seq
         * @param fromUserId    来源用户ID
         * @param fromUserName  来源用户名
         * @param roomId        房间ID
         */
        @Override
        public void onInviteJoinLiveRequest(int seq, String fromUserId, String fromUserName, String roomId) {
            recordLog("收到连麦邀请, seq: %d; roomId: %s; fromUserId: %s; fromUserName: %s", seq, roomId, fromUserId, fromUserName);
        }

        /**
         * 视频宽高变化通知,startPlay后，如果视频宽度或者高度发生变化(首次的值也会)，则收到该通知.
         *
         * @param streamId  流ID
         * @param width     视频宽度
         * @param height    视频高度
         */
        @Override
        public void onVideoSizeChangedTo(String streamId, int width, int height) {
            recordLog("收到帧数据, streamId: %s; width: %d; height: %d", streamId, width, height);
        }
    }

    private class ZegoIMCallback implements IZegoIMCallback {
        /**
         * 房间成员更新回调.
         *
         * @param listUser     成员更新列表
         * @param updateType   @see com.zego.zegoliveroom.constants.ZegoIM#UserUpdateType
         */
        @Override
        public void onUserUpdate(ZegoUserState[] listUser, int updateType) {
            recordLog("房间成员有更新, updateType: %d; UserCount: %d", updateType, listUser.length);
            for (ZegoUserState user : listUser) {
                if (user.roomRole == ZegoConstants.RoomRole.Anchor && user.updateFlag == ZegoIM.UserUpdateFlag.Deleted) {
                    notifyAnchorLogout();
                    break;
                }

                if (user.updateFlag == ZegoIM.UserUpdateFlag.Added) {
                    recordLog("%s 进入房间，等待主持人处理", user.userName);
                } else if (user.updateFlag == ZegoIM.UserUpdateFlag.Deleted) {
                    removeMemberById(user.userID);
                }
            }
        }

        /**
         * 收到房间的广播消息.
         *
         * @param roomId        房间ID
         * @param listMsg       消息列表, 包括消息内容，消息分类，消息类型，发送者等信息
         */
        @Override
        public void onRecvRoomMessage(String roomId, ZegoRoomMessage[] listMsg) {
            recordLog("收到房间消息，roomId: " + roomId);
        }

        /**
         * 收到会话消息.
         *
         * @param roomId            房间ID
         * @param conversationId    会话ID
         * @param message           会话消息, 包括消息内容，消息类型，发送者，发送时间等信息
         */
        @Override
        public void onRecvConversationMessage(String roomId, String conversationId, ZegoConversationMessage message) {
            recordLog("收到会话消息, roomId: %s; conversationId: %s", roomId, conversationId);
        }

        @Override
        public void onUpdateOnlineCount(String s, int i) {
            recordLog("Online Count: " + i);
        }

        @Override
        public void onRecvBigRoomMessage(String s, ZegoBigRoomMessage[] zegoBigRoomMessages) {

        }
    }

    private class ZegoRoomCallback implements IZegoRoomCallback {
        /**
         * 因为登陆抢占原因等被挤出房间.
         *
         * @param reason    原因
         * @param roomId    房间ID
         */
        @Override
        public void onKickOut(int reason, String roomId) {
            recordLog("被挤出房间, reason: %d; roomId: %s", reason, roomId);
        }

        /**
         * 与 server 断开.
         *
         * @param errorCode  错误码
         * @param roomId     房间ID
         */
        @Override
        public void onDisconnect(int errorCode, String roomId) {
            recordLog("连接丢失, errorCode: %d; roomId: %s", errorCode, roomId);
        }

        @Override
        public void onReconnect(int i, String s) {

        }

        @Override
        public void onTempBroken(int i, String s) {

        }

        /**
         *  房间流列表更新.
         *
         * @param type          2001:增加, 2002:删除
         * @param listStream    流列表
         * @param roomId        房间ID
         */
        @Override
        public void onStreamUpdated(int type, ZegoStreamInfo[] listStream, String roomId) {
            recordLog("有流更新, type: %d; roomId: %s; streamCount: %d", type, roomId, listStream.length);
            if (listStream == null || listStream.length == 0 || TextUtils.isEmpty(roomId)) {
                // 无效流信息，忽略
            } else if (allWolfMembers.size() == 0) {
                // 信令到达前的流更新，暂存

            } else {
                switch (type) {
                    case ZegoConstants.StreamUpdateType.Added:
                        handleStreamAdded(listStream, roomId);
                        break;

                    case ZegoConstants.StreamUpdateType.Deleted:
                        handleStreamDeleted(listStream, roomId);
                        break;
                }
            }
        }

        /**
         * 更新流的额外信息.
         * @param listStream
         * @param roomId
         */
        @Override
        public void onStreamExtraInfoUpdated(ZegoStreamInfo[] listStream, String roomId) {
            recordLog("有流更新Ex, roomId: %s; streamCount: %d", roomId, listStream.length);
        }

        /**
         * 收到自定义消息.
         *
         * @param fromUserId     消息来源UserID
         * @param fromUserName   消息来源UserName
         * @param content    消息内容
         * @param roomId     房间ID
         */
        @Override
        public void onRecvCustomCommand(String fromUserId, String fromUserName, String content, String roomId) {
            recordLog("收到自定义消息, fromUserId: %s; fromUserName: %s; roomId: %s; content: %s", fromUserId, fromUserName, roomId, content);
            JSONObject json = (JSONObject) JsonUtil.safeDecodeFromString(content);
            int command = json.optInt(kSpeakingCommandKey, 0);
            switch (command) {
                case SpeakingCmd.AnswerRoomInfo:
                    handleAnswerRoomInfoCommand(json);
                    break;

                case SpeakingCmd.AllowSpeaking:
                    handleAllowSpeakingCommand(json);
                    break;

                case SpeakingCmd.StartSpeaking:
                    handleStartSpeakingCommand(json);
                    break;

                case SpeakingCmd.StopSpeaking:
                    handleStopSpeakingCommand(json);
                    break;

                case SpeakingCmd.NewUserJoinRoom:
                    handleNewUserJoinRoomCommand(json);
                    break;

                case SpeakingCmd.UserLeaveRoom:
                    handleUserLeaveRoomCommand(json);
                    break;

                case SpeakingCmd.InTurnSpeaking:
                    handleInTurnSpeakingCommand(json);
                    break;

                case SpeakingCmd.FreeSpeaking:
                    handleFreeSpeakingCommand(json);
                    break;

                default:
                    recordLog("参与者无需处理此消息，command: %d", command);
                    break;
            }
        }
    }
}
