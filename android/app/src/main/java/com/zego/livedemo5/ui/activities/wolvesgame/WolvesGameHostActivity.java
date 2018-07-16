package com.zego.livedemo5.ui.activities.wolvesgame;

import android.app.Activity;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Rect;
import android.os.Bundle;
import android.os.Message;
import android.support.v7.app.AlertDialog;
import android.text.TextUtils;
import android.view.Surface;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Toast;

import com.zego.livedemo5.R;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.utils.JsonUtil;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.livedemo5.utils.ZegoRoomUtil;
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

import java.lang.ref.WeakReference;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Random;

import butterknife.OnClick;

public class WolvesGameHostActivity extends WolvesGameBaseActivity {
//    private int appOrientation = Surface.ROTATION_0;

    private int currentIndex;
    private int currentSpeakingIndex;
    private String currentSpeakingUserId;

    private int myCharacter;

    /**
     * 当前参与游戏的人员列表
     */
    private LinkedList<WolfInfo> inGamingMembers;



    public static void actionStart(Activity activity, String publishTitle, int appOrientation) {
        Intent intent = new Intent(activity, WolvesGameHostActivity.class);
        intent.putExtra(IntentExtra.PUBLISH_TITLE, publishTitle);
        intent.putExtra(IntentExtra.APP_ORIENTATION, appOrientation);
        activity.startActivity(intent);
        activity.overridePendingTransition(R.anim.scale_translate,
                R.anim.my_alpha_action);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();

        allWolfMembers.clear();
        inGamingMembers.clear();

        stopCurrentMode();

        zegoLiveRoom.setZegoLivePublisherCallback(null);
        zegoLiveRoom.setZegoLivePlayerCallback(null);
        zegoLiveRoom.setZegoRoomCallback(null);
        zegoLiveRoom.setZegoIMCallback(null);

        if (hasLoginRoom) {
            boolean logoutSuccess = zegoLiveRoom.logoutRoom();
            recordLog("退出房间成功？%s", logoutSuccess);
        }

        mHandler.removeCallbacksAndMessages(null);
    }

    /**
     * 初始化从外部传递过来的数据.
     */
    @Override
    protected void initExtraData(Bundle savedInstanceState) {
        if (savedInstanceState == null) {
            Intent intent = getIntent();
            String publishTitle = intent.getStringExtra(IntentExtra.PUBLISH_TITLE);
            if (TextUtils.isEmpty(publishTitle)) {
                roomName += PreferenceUtil.getInstance().getUserName();
            } else {
                roomName = publishTitle;
            }
//            appOrientation = intent.getIntExtra(IntentExtra.APP_ORIENTATION, Surface.ROTATION_0);
        }
    }

    /**
     * 初始化子类中的变量.
     */
    @Override
    protected void initVariables(Bundle savedInstanceState) {
        super.initVariables(savedInstanceState);
        currentSpeakingMode = SpeakingMode.FreeSpeakingMode;

        inGamingMembers = new LinkedList<>();
    }

    /**
     * 加载数据.
     */
    @Override
    protected void doBusiness(Bundle savedInstanceState) {
        showSelectPublishWayDialog();
    }

    @OnClick({R.id.btn_start_or_stop_speaking, R.id.in_turn_speaking, R.id.end_in_turn_speaking})
    public void onButtonClick(View view) {
        switch (view.getId()) {
            case R.id.btn_start_or_stop_speaking:
                onSpeakingButtonClick();
                break;

            case R.id.in_turn_speaking:
                onStartInTurnSpeakingMode();
                break;

            case R.id.end_in_turn_speaking:
                onEndInTurnSpeakingMode();
                break;
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
                stopTalking();
                return true;

            case MsgIds.NOTIFY_OTHER_STOP_SPEAKING:
                String userId = (String) msg.obj;
                reportStopSpeaking(userId, true);
                return false;

            default:
                return super.handleUIMessage(msg);
        }
    }

    private void sendStopSpeakingCommand(String userId, IZegoCustomCommandCallback callback) {
        JSONObject json = new JSONObject();
        try {
            json.put(kSpeakingCommandKey, SpeakingCmd.StopSpeaking);
            json.put(kSpeakingUserIdKey, userId);
        } catch (JSONException e) {
        }

        zegoLiveRoom.sendCustomCommand(getCurrentMembers(), json.toString(), callback);
    }

    private void reportStopSpeaking(final String userId, final boolean notifyNextSpeaker) {
        sendStopSpeakingCommand(userId, new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("通知 %s 停止说话返回：%d", userId, errorCode);

                if (notifyNextSpeaker) {
                    arrangeNextSpeaker();
                }
            }
        });
    }

    private void onStopSpeaking() {
        mBtnSpeaking.setText(R.string.start_speaking);
        if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
            unBindStreamFromSpeakingHeaderViewAndHide();

            mBtnSpeaking.setEnabled(false);
            mTextTips.setText(R.string.mode_in_turn_speaking);

            mHandler.removeMessages(MsgIds.UPDATE_COUNT_TIMER);
            reportStopSpeaking(PreferenceUtil.getInstance().getUserID(), true);
        } else {
            mBtnSpeaking.setEnabled(true);
            mTextTips.setText(R.string.mode_free_speaking);
            reportStopSpeaking(PreferenceUtil.getInstance().getUserID(), false);
        }
    }

    private void stopTalking() {
        WolfInfo myInfo = getMyInfo();
        if (myInfo == null) return;

        stopPublish();
        if (currentPublishMode != PublishMode.Super_Low_Delay) {
            myInfo.setStreamId(null);
        }
        myInfo.setState(WolfInfo.SpeakingState.isIdle);
        mRecyclerAdapter.updateItem(myInfo);

        onStopSpeaking();
    }

    private void onSpeakingButtonClick() {
        if (isSpeaking) {
            mHandler.removeMessages(MsgIds.STOP_SPEAKING_FOR_ME);
            stopTalking();
        } else {
            startTalking();
        }
    }

    private void stopPublish() {
        zegoLiveRoom.stopPreview();
        zegoLiveRoom.setPreviewView(null);
        zegoLiveRoom.enableMic(false);
        zegoLiveRoom.enableCamera(false);
        if (currentPublishMode != PublishMode.Super_Low_Delay) {
            zegoLiveRoom.stopPublishing();
        }

        isSpeaking = false;
    }

    private void stopPlay(String streamId) {
        if (TextUtils.isEmpty(streamId)) return;

//        if (currentPublishMode != PublishMode.Super_Low_Delay) {
            zegoLiveRoom.stopPlayingStream(streamId);
//        }
    }

    private HashMap<Integer, String> randomCharacter() {
        int count = inGamingMembers.size();
        HashMap<Integer, String> characters = new HashMap<>(count);
        Random randomIns = new Random();
        for (WolfInfo wolf : inGamingMembers) {
            int character = randomIns.nextInt(count) + 1;
            while (characters.containsKey(character)) {
                character = randomIns.nextInt(count) + 1;
            }

            String userId = wolf.getUserId();
            characters.put(character, userId);

            if (myCharacter == 0 && isMe(userId)) {
                myCharacter = character;
            }
        }
        return characters;
    }

    private void sendStartInTurnSpeakingModeCommand(IZegoCustomCommandCallback callback) {
        HashMap<Integer, String> characters = randomCharacter();
        JSONObject jsonCmd = new JSONObject();
        try {
            JSONObject jsonCharacters = new JSONObject();
            for (Map.Entry<Integer, String> entry : characters.entrySet()) {
                jsonCharacters.put(entry.getValue(), entry.getKey());
            }
            jsonCmd.put(kSpeakingCommandKey, SpeakingCmd.InTurnSpeaking);
            jsonCmd.put(kUserCharacterKey, jsonCharacters);
        } catch (JSONException e) {

        }

        zegoLiveRoom.sendCustomCommand(getCurrentInGamingMembers(), jsonCmd.toString(), callback);
    }

    private void stopCurrentMode() {
        // stop current mode
        for (WolfInfo wolf : allWolfMembers) {
            if (wolf == null) continue;

            String streamId = wolf.getStreamId();
            if (TextUtils.isEmpty(streamId)) continue;

            if (isMe(wolf.getUserId())) {
                stopPublish();
            } else {
                stopPlay(streamId);
            }

            wolf.setState(WolfInfo.SpeakingState.isIdle);
            if (currentPublishMode != PublishMode.Super_Low_Delay) {
                wolf.setStreamId(null);
            }
            mRecyclerAdapter.updateItem(wolf);
        }
    }

    private void onStartInTurnSpeakingMode() {
        stopCurrentMode();

        inGamingMembers.clear();
        inGamingMembers.addAll(allWolfMembers);

        mHandler.removeCallbacksAndMessages(null);
        sendStartInTurnSpeakingModeCommand(new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("切换到轮流说话模式，errorCode: %d", errorCode);
                if (errorCode == 0) {
                    mTextRole.setText(getString(R.string.wolf_role, myCharacter));
                    mTextRole.setVisibility(View.VISIBLE);

                    currentSpeakingIndex = 0;
                    currentSpeakingMode = SpeakingMode.InTurnSpeakingMode;

                    mInTurnSpeaking.setEnabled(false);
                    mEndInTurnSpeaking.setEnabled(true);
                    mTextTips.setText(R.string.mode_in_turn_speaking);

                    mRecyclerAdapter.setSpeakingModeAndPublishMode(SpeakingMode.InTurnSpeakingMode, currentPublishMode);

                    arrangeNextSpeaker();
                }
            }
        });
    }

    private void broadFreeSpeaking() {
        JSONObject jsonCmd = new JSONObject();
        try {
            jsonCmd.put(kSpeakingCommandKey, SpeakingCmd.FreeSpeaking);
        } catch (JSONException e) {

        }
        zegoLiveRoom.sendCustomCommand(getCurrentMembers(), jsonCmd.toString(), new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("切换到自由说话模式，errorCode: %d", errorCode);

                currentSpeakingMode = SpeakingMode.FreeSpeakingMode;
                mBtnSpeaking.setEnabled(true);
                mTextTips.setText(R.string.mode_free_speaking);

                mRecyclerAdapter.setSpeakingModeAndPublishMode(SpeakingMode.FreeSpeakingMode, currentPublishMode);
            }
        });
    }

    private void onEndInTurnSpeakingMode() {
        mHandler.removeCallbacksAndMessages(null);

        inGamingMembers.clear();
        mEndInTurnSpeaking.setEnabled(false);
        mInTurnSpeaking.setEnabled(true);
        mTextRole.setVisibility(View.INVISIBLE);
        mTimerView.setVisibility(View.INVISIBLE);
        mBtnSpeaking.setEnabled(true);

        stopCurrentMode();
        currentSpeakingIndex = 0;
        currentSpeakingUserId = "";

        mCurrentSpeakingHead.setVisibility(View.GONE);

        broadFreeSpeaking();
    }

    private void showSelectPublishWayDialog() {
        String[] publishWays = new String[] {
                getString(R.string.publish_way_low_delay), getString(R.string.publish_way_low_cost)
        };
        final AlertDialog.Builder dialogBuilder = new AlertDialog.Builder(this);
        dialogBuilder.setTitle(R.string.publish_way_title)
                .setAdapter(new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, android.R.id.text1, publishWays), new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        switch (which) {
                            case 0:
                                currentPublishMode = PublishMode.Super_Low_Delay;
                                break;

                            case 1:
                                currentPublishMode = PublishMode.Low_Cost;
                                break;
                        }
                        _doBusiness();
                    }
                });
        dialogBuilder.setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                onBackPressed();
            }
        });

        dialogBuilder.create().show();
    }

    private void _doBusiness() {
        roomId = ZegoRoomUtil.getRoomID(ZegoRoomUtil.ROOM_TYPE_WOLF);
        zegoLiveRoom.setRoomConfig(false, true);
        zegoLiveRoom.setZegoLivePublisherCallback(new ZegoLivePublisherCallback());
        zegoLiveRoom.setZegoLivePlayerCallback(new ZegoLivePlayerCallback());
        zegoLiveRoom.setZegoRoomCallback(new ZegoRoomCallback());
        zegoLiveRoom.setZegoIMCallback(new ZegoIMCallback());
        zegoLiveRoom.loginRoom(roomId, roomName, ZegoConstants.RoomRole.Anchor, new IZegoLoginCompletionCallback() {
            @Override
            public void onLoginCompletion(int errorCode, ZegoStreamInfo[] zegoStreamInfos) {
                if (isFinishing()) return;

                if (errorCode == 0) {
                    hasLoginRoom = true;
                    mTextTips.setText(R.string.tips_login_success);
                    recordLog("登录房间成功. roomId: " + roomId);

                    currentIndex = 1;
                    WolfInfo wolf = new WolfInfo(PreferenceUtil.getInstance().getUserID(), PreferenceUtil.getInstance().getUserName());
                    wolf.setIndex(currentIndex);
                    allWolfMembers.add(wolf);
                    mRecyclerAdapter.updateData(allWolfMembers);

                    mBtnSpeaking.setEnabled(true);
                    mTextTips.setText(R.string.mode_free_speaking);

                    if (currentPublishMode == PublishMode.Super_Low_Delay) {
                        String streamId = publishWithoutPreview(roomName);
                        WolfInfo myInfo = getMyInfo();
                        myInfo.setStreamId(streamId);
                    }
                } else {
                    mTextTips.setText(getString(R.string.tips_login_failed, errorCode));
                    recordLog("登录房间失败. errorCode: " + errorCode);
                }
            }
        });
    }

    private void resetPlayViewAndStop(String userId) {
        WolfInfo wolf = getWolfById(userId);
        if (wolf == null) return;

        zegoLiveRoom.stopPlayingStream(wolf.getStreamId());
        wolf.setState(WolfInfo.SpeakingState.isIdle);
        if (currentPublishMode != PublishMode.Super_Low_Delay) {
            wolf.setStreamId(null);
        }
        mRecyclerAdapter.updateItem(wolf);

        if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
            unBindStreamFromSpeakingHeaderViewAndHide();
        }
    }

    private void sendAllowSpeakingCommand(String userId, IZegoCustomCommandCallback callback) {
        JSONObject json = new JSONObject();
        try {
            json.put(kSpeakingCommandKey, SpeakingCmd.AllowSpeaking);
            json.put(kSpeakingUserIdKey, userId);
        } catch (JSONException e) {

        }

        zegoLiveRoom.sendCustomCommand(getCurrentMembers(), json.toString(), callback);
    }

    private void arrangeNextSpeaker() {
        int index = 0;
        int minDelta = Integer.MAX_VALUE;
        for (WolfInfo wolf : inGamingMembers) {
            if (wolf.getIndex() > currentSpeakingIndex && wolf.getIndex() - currentSpeakingIndex < minDelta) {
                minDelta = wolf.getIndex() - currentSpeakingIndex;
                index = inGamingMembers.indexOf(wolf);
            }
        }

        if (index >= inGamingMembers.size()) {
            recordLog("索引越界了，index: %d, inGamingMembers's count: %d", index, inGamingMembers.size());
            return;
        }

        final WolfInfo wolf = inGamingMembers.get(index);
        currentSpeakingIndex = wolf.getIndex();
        currentSpeakingUserId = wolf.getUserId();

        recordLog("允许下一个说话的人: %d-%s", wolf.getIndex(), wolf.getUserName());

        if (isMe(currentSpeakingUserId)) {
            mBtnSpeaking.setText(R.string.start_speaking);
            mBtnSpeaking.setEnabled(true);

            mHandler.sendEmptyMessageDelayed(MsgIds.STOP_SPEAKING_FOR_ME, kSpeakingTimerInterval * 1000);  // 60s后不论有没有开始说话，都必须停止说话
        }

        sendAllowSpeakingCommand(wolf.getUserId(), new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("发送允许指令返回：%d", errorCode);
                if (errorCode == 0) {
                    Message updateMsg = Message.obtain(mHandler, MsgIds.UPDATE_COUNT_TIMER, kSpeakingTimerInterval, 0);
                    updateMsg.sendToTarget();

                    String userId = wolf.getUserId();
                    if (!isMe(userId)) {
                        Message notifyMsg = Message.obtain(mHandler, MsgIds.NOTIFY_OTHER_STOP_SPEAKING, userId);
                        mHandler.sendMessageDelayed(notifyMsg, kAnchorTimerInterval * 1000);
                    }

                    wolf.setState(WolfInfo.SpeakingState.allowSpeaking);
                    mRecyclerAdapter.updateItem(wolf);
                } else if (errorCode == -2) {
                    Toast.makeText(WolvesGameHostActivity.this, "操作太频繁，延迟处理", Toast.LENGTH_LONG).show();
                    final WeakReference<IZegoCustomCommandCallback> callbackRef = new WeakReference<IZegoCustomCommandCallback>(this);
                    mHandler.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            IZegoCustomCommandCallback callback = callbackRef.get();
                            if (callback == null) {
                                Toast.makeText(WolvesGameHostActivity.this, "发送指令时出错)", Toast.LENGTH_LONG).show();
                            } else{
                                sendAllowSpeakingCommand(wolf.getUserId(), callbackRef.get());
                            }
                        }
                    }, 5000);
                } else {
                    Toast.makeText(WolvesGameHostActivity.this, "发送指令时出错(err:" + errorCode + ")", Toast.LENGTH_LONG).show();
                }
            }
        });
    }

    private void handleStopSpeakingCommand(JSONObject json) {
        String userId = json.optString(kSpeakingUserIdKey);
        if (isMe(userId)) return;

        mHandler.removeMessages(MsgIds.UPDATE_COUNT_TIMER);
        mHandler.removeMessages(MsgIds.NOTIFY_OTHER_STOP_SPEAKING);

        resetPlayViewAndStop(userId);
        if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
            arrangeNextSpeaker();
        }
    }

    private void handleAnswerRoomInfoCommand(String userId, String userName) {
        removeOlderUser(userId, true);

        currentIndex ++;

        ZegoUser zegoUser = new ZegoUser();
        zegoUser.userID = userId;
        zegoUser.userName = userName;
        sendAnswerRoomInfoCommand(zegoUser, new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("回复新加入狼消息返回，errorCode: %d; roomId: %s", errorCode, roomId);
            }
        });

        // 通知其他人有新狼加入
        WolfInfo newWolf = new WolfInfo(zegoUser);
        newWolf.setIndex(currentIndex);
        sendNewUserJoinRoomCommand(newWolf, new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("通知新狼加入消息返回，errorCode: %d; roomId: %s", errorCode, roomId);
            }
        });

        allWolfMembers.add(newWolf);
        mRecyclerAdapter.insertItem(newWolf);

        if (currentSpeakingMode == SpeakingMode.FreeSpeakingMode) {
            mInTurnSpeaking.setEnabled(true);
        }
    }

    private void sendAnswerRoomInfoCommand(ZegoUser toUser, IZegoCustomCommandCallback callback) {
        JSONObject cmdJson = new JSONObject();
        try {
            cmdJson.put(kSpeakingCommandKey, SpeakingCmd.AnswerRoomInfo);
            cmdJson.put(kUserIndexKey, currentIndex);
            cmdJson.put(kSpeakingModeKey, currentSpeakingMode);
            cmdJson.put(kServerModeIndexKey, currentPublishMode == PublishMode.Super_Low_Delay || currentPublishMode == PublishMode.Low_Delay);
            cmdJson.put(kSuperLowDelayMode, currentPublishMode == PublishMode.Super_Low_Delay);

            JSONArray wolves = new JSONArray();
            for (WolfInfo wolf : allWolfMembers) {
                JSONObject wolfJson = encodeWolfInfo(wolf);
                wolves.put(wolfJson);
            }
            cmdJson.put(kCurrentUserListKey, wolves);
        } catch (JSONException e) {
        }

        zegoLiveRoom.sendCustomCommand(new ZegoUser[] { toUser }, cmdJson.toString(), callback);
    }

    private void sendNewUserJoinRoomCommand(WolfInfo newWolf, IZegoCustomCommandCallback callback) {
        JSONObject newUserJoinCmd = new JSONObject();
        try {
            newUserJoinCmd.put(kSpeakingCommandKey, SpeakingCmd.NewUserJoinRoom);
            newUserJoinCmd.put(kNewUserKey, encodeWolfInfo(newWolf));
        } catch (JSONException e) {
        }

        zegoLiveRoom.sendCustomCommand(getCurrentMembers(), newUserJoinCmd.toString(), callback);
    }

    private void broadUserLeave(final String userId) {
        JSONObject json = new JSONObject();
        try {
            json.put(kSpeakingCommandKey, SpeakingCmd.UserLeaveRoom);
            json.put(kSpeakingUserIdKey, userId);
        } catch (JSONException e) {

        }

        zegoLiveRoom.sendCustomCommand(getCurrentMembers(), json.toString(), new IZegoCustomCommandCallback() {
            @Override
            public void onSendCustomCommand(int errorCode, String roomId) {
                recordLog("通知有用户离开, errorCode: %d, userId: %s", errorCode, userId);
            }
        });
    }

    private void removeOlderUser(String userId, boolean broadcast) {
        WolfInfo wolf = getWolfById(userId);
        if (wolf == null) return;

        if (!TextUtils.isEmpty(wolf.getStreamId())) {
            stopPlay(wolf.getStreamId());
            wolf.setStreamId(null);
        }

        allWolfMembers.remove(wolf);
        mRecyclerAdapter.deleteItem(wolf);

        if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
            for (WolfInfo _wolf : inGamingMembers) {
                if (userId.equals(_wolf.getUserId())) {
                    inGamingMembers.remove(_wolf);
                    break;
                }
            }

            if (inGamingMembers.size() < 2) {
                mInTurnSpeaking.setEnabled(false);
                mEndInTurnSpeaking.setEnabled(false);

                stopCurrentMode();
                currentSpeakingMode = SpeakingMode.FreeSpeakingMode;
                mBtnSpeaking.setEnabled(true);

                mTextTips.setText(R.string.tips_all_members_leave);
            }
        }

        if (broadcast) {
            broadUserLeave(userId);
        }
    }

    private ZegoUser[] getCurrentInGamingMembers() {
        ZegoUser[] members = new ZegoUser[inGamingMembers.size()];
        int index = 0;
        for (WolfInfo wolf : inGamingMembers) {
            members[index++] = wolf;
        }
        return members;
    }

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

                isSpeaking = true;
                if (currentSpeakingIndex == SpeakingMode.FreeSpeakingMode) {
                    mTextTips.setText(R.string.mode_update_system_success);
                } else {
                    mTextTips.setText(R.string.is_speaking);
                }

                WolfInfo myInfo = getMyInfo();
                if (myInfo == null) return;

                myInfo.setState(WolfInfo.SpeakingState.isSpeaking);
                mRecyclerAdapter.updateItem(myInfo);

                if (currentSpeakingMode == SpeakingMode.InTurnSpeakingMode) {
                    bindStream2SpeakingHeaderViewAndShow(streamId);

                    zegoLiveRoom.setPreviewView(mCurrentSpeakingHead);
                    zegoLiveRoom.setPreviewViewMode(ZegoVideoViewMode.ScaleAspectFill);
                    zegoLiveRoom.startPreview();
                }
            } else {
                WolfInfo myInfo = getMyInfo();
                if (myInfo == null || !TextUtils.equals(myInfo.getStreamId(), streamId)) return;

                myInfo.setState(WolfInfo.SpeakingState.isIdle);
                myInfo.setStreamId(null);
                mTextTips.setText(R.string.mode_update_system_failed);

                String errorMsg;
                if (stateCode == 1) {
                    errorMsg = getString(R.string.tips_publish_failed, stateCode, streamId);
                } else {
                    errorMsg = getString(R.string.tips_publish_finish, stateCode, streamId);
                }
                mTextTips.setText(errorMsg);
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

        @Override
        public void onRecvEndJoinLiveCommand(String fromUserId, String fromUserName, String roomId) {
            recordLog("onRecvEndJoinLiveCommand, from userId: %s, from userName: %s, roomId: %s", fromUserId, fromUserName, roomId);
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
            if (updateType == ZegoIM.UserUpdateType.Total) {
                //TODO
            } else if (updateType == ZegoIM.UserUpdateType.Increase) {
                for (ZegoUserState userState : listUser) {
                    if (userState.updateFlag == ZegoIM.UserUpdateFlag.Added) {
                        //TODO
                    } else if (userState.updateFlag == ZegoIM.UserUpdateFlag.Deleted) {
                        removeOlderUser(userState.userID, true);
                    }
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
            JSONObject json = (JSONObject)JsonUtil.safeDecodeFromString(content);
            int command = json.optInt(kSpeakingCommandKey, 0);
            switch (command) {
                case SpeakingCmd.StopSpeaking: {
                    handleStopSpeakingCommand(json);
                }
                    break;

                case SpeakingCmd.StartSpeaking:
                    handleStartSpeakingCommand(json);
                    break;

                case SpeakingCmd.AskRoomInfo: {
                    handleAnswerRoomInfoCommand(fromUserId, fromUserName);
                }
                    break;

                case SpeakingCmd.UserLeaveRoom: {
                    String userId = json.optString(kSpeakingUserIdKey);
                    if (isMe(userId)) return;

                    removeOlderUser(userId, false);
                }
                    break;

                default:
                    recordLog("主播忽略消息, fromUserName: %s; Command: %d", fromUserName, command);
                    break;
            }
        }
    }
}
