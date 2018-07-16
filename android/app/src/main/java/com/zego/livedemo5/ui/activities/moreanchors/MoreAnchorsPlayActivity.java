package com.zego.livedemo5.ui.activities.moreanchors;

import android.app.Activity;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

import com.zego.livedemo5.R;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.presenters.RoomInfo;
import com.zego.livedemo5.ui.activities.BasePlayActivity;
import com.zego.livedemo5.ui.widgets.ViewLive;
import com.zego.zegoavkit2.soundlevel.IZegoSoundLevelCallback;
import com.zego.zegoavkit2.soundlevel.ZegoSoundLevelInfo;
import com.zego.zegoavkit2.soundlevel.ZegoSoundLevelMonitor;
import com.zego.zegoliveroom.callback.IZegoLivePlayerCallback;
import com.zego.zegoliveroom.callback.IZegoLivePublisherCallback;
import com.zego.zegoliveroom.callback.IZegoLoginCompletionCallback;
import com.zego.zegoliveroom.callback.IZegoRoomCallback;
import com.zego.zegoliveroom.callback.im.IZegoIMCallback;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.entity.AuxData;
import com.zego.zegoliveroom.entity.ZegoBigRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamQuality;
import com.zego.zegoliveroom.entity.ZegoConversationMessage;
import com.zego.zegoliveroom.entity.ZegoRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;
import com.zego.zegoliveroom.entity.ZegoUserState;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class MoreAnchorsPlayActivity extends BasePlayActivity {

    /**
     * 启动入口.
     *
     * @param activity 源activity
     * @param roomInfo 房间信息
     */
    public static void actionStart(Activity activity, RoomInfo roomInfo) {
        Intent intent = new Intent(activity, MoreAnchorsPlayActivity.class);
        intent.putExtra(IntentExtra.ROOM_ID, roomInfo.room_id);

        ArrayList<String> streamList = getStremListFromRoomInfo(roomInfo);
        intent.putStringArrayListExtra(IntentExtra.LIST_STREAM, streamList);

        activity.startActivity(intent);
        activity.overridePendingTransition(R.anim.scale_translate,
                R.anim.my_alpha_action);
    }



    @Override
    protected void doBusiness(Bundle savedInstanceState) {
        super.doBusiness(savedInstanceState);

        mZegoLiveRoom.loginRoom(mRoomID, ZegoConstants.RoomRole.Audience, new IZegoLoginCompletionCallback() {
            @Override
            public void onLoginCompletion(int errorCode, ZegoStreamInfo[] zegoStreamInfos) {
                if(errorCode == 0){
                    handleAudienceLoginRoomSuccess(zegoStreamInfos);
                }else {
                    handleAudienceLoginRoomFail(errorCode);
                }
            }
        });

        mZegoLiveRoom.setZegoLivePublisherCallback(new IZegoLivePublisherCallback() {
            @Override
            public void onPublishStateUpdate(int stateCode, String streamID, HashMap<String, Object> streamInfo) {
                //推流状态更新
                if(stateCode == 0){
                    handlePublishSucc(streamID, streamInfo);
                }else {
                    handlePublishStop(stateCode, streamID);
                }
            }

            @Override
            public void onJoinLiveRequest(final int seq, String fromUserID, String fromUserName, String roomID) {
            }

            @Override
            public void onPublishQualityUpdate(String streamID, ZegoStreamQuality streamQuality) {
                // 推流质量回调
                handlePublishQualityUpdate(streamID, streamQuality.quality, streamQuality.videoFPS, streamQuality.videoBitrate);
            }

            @Override
            public AuxData onAuxCallback(int dataLen) {
                return handleAuxCallback(dataLen);
            }

            @Override
            public void onCaptureVideoSizeChangedTo(int width, int height){

            }

            @Override
            public void onMixStreamConfigUpdate(int errorCode, String streamID, HashMap<String, Object> streamInfo) {

            }
        });

        mZegoLiveRoom.setZegoLivePlayerCallback(new IZegoLivePlayerCallback() {
            @Override
            public void  onPlayStateUpdate(int stateCode, String streamID) {
                // 拉流状态更新
                if(stateCode == 0){
                    handlePlaySucc(streamID);
                }else {
                    handlePlayStop(stateCode, streamID);
                }
            }

            @Override
            public void onPlayQualityUpdate(String streamID, ZegoStreamQuality streamQuality) {
                // 拉流质量回调
                handlePlayQualityUpdate(streamID, streamQuality.quality, streamQuality.videoFPS, streamQuality.videoBitrate);
            }

            @Override
            public void onInviteJoinLiveRequest(int seq, String fromUserID, String fromUserName, String roomID) {

            }

            @Override
            public void onRecvEndJoinLiveCommand(String fromUserId, String fromUserName, String roomId) {
                handleEndJoinLiveCommand(fromUserId, fromUserName, roomId);
            }

            @Override
            public void onVideoSizeChangedTo(String streamID, int width, int height) {
                handleVideoSizeChanged(streamID, width, height);
            }
        });

        mZegoLiveRoom.setZegoRoomCallback(new IZegoRoomCallback() {
            @Override
            public void onKickOut(int reason, String roomID){

            }

            @Override
            public void onDisconnect(int errorCode, String roomID) {
                handleDisconnect(errorCode, roomID);
            }

            @Override
            public void onReconnect(int i, String s) {

            }

            @Override
            public void onTempBroken(int i, String s) {

            }

            @Override
            public void onStreamUpdated(final int type, final ZegoStreamInfo[] listStream, final String roomID) {
                if(listStream != null && listStream.length > 0){
                    switch (type){
                        case ZegoConstants.StreamUpdateType.Added:
                            handleStreamAdded(listStream, roomID);
                            break;
                        case ZegoConstants.StreamUpdateType.Deleted:
                            handleStreamDeleted(listStream, roomID);
                            break;
                    }
                }
            }

            @Override
            public void onStreamExtraInfoUpdated(ZegoStreamInfo[] listStream, String roomID) {
            }

            @Override
            public void onRecvCustomCommand(String userID, String userName, String content, String roomID) {
            }
        });

        mZegoLiveRoom.setZegoIMCallback(new IZegoIMCallback() {

            @Override
            public void onUserUpdate(ZegoUserState[] listUser, int updateType){
                handleUserUpdate(listUser, updateType);
            }

            @Override
            public void onRecvRoomMessage(String roomID, ZegoRoomMessage[] listMsg){
                handleRecvRoomMsg(roomID, listMsg);
            }

            @Override
            public void onRecvConversationMessage(String roomID, String conversationID, ZegoConversationMessage message){
                handleRecvConversationMsg(roomID, conversationID, message);
            }

            @Override
            public void onUpdateOnlineCount(String s, int i) {
                recordLog("Online Count: " + i);
            }

            @Override
            public void onRecvBigRoomMessage(String s, ZegoBigRoomMessage[] zegoBigRoomMessages) {
                
            }
        });

        // 播放从房间列表传过来的流列表
        if (mOldSavedStreamList != null && mOldSavedStreamList.size() > 0) {
            for (String streamId : mOldSavedStreamList) {
                Log.w("MoreAnchorsPlayA", "Quick play: " + streamId);
                startPlay(streamId);

                ZegoSoundLevelMonitor.getInstance().setCycle(2000);
                ZegoSoundLevelMonitor.getInstance().setCallback(new IZegoSoundLevelCallback() {
                    @Override
                    public void onSoundLevelUpdate(ZegoSoundLevelInfo[] zegoSoundLevelInfos) {
                        Log.w("RUEI", "onSoundLevelUpdate");
                        for (ZegoSoundLevelInfo info : zegoSoundLevelInfos) {
                            Log.w("RUEI", "   --streamId: " + info.streamID + "; level: " + info.soundLevel);
                        }
                    }

                    @Override
                    public void onCaptureSoundLevelUpdate(ZegoSoundLevelInfo zegoSoundLevelInfo) {
                        Log.w("RUEI", "onCaptureSoundLevelUpdate, zegoSoundLevelInfo.soundLevel: " + zegoSoundLevelInfo.soundLevel);
                    }
                });
                ZegoSoundLevelMonitor.getInstance().start();
            }
        }
    }

    @Override
    protected void initPublishControlText() {
        if (mIsPublishing) {
            mTvPublisnControl.setText(R.string.stop_publishing);
            mTvPublishSetting.setEnabled(true);
        } else {
            mTvPublisnControl.setText(R.string.request_to_join);
            mTvPublishSetting.setEnabled(false);
        }
    }

    @Override
    protected void hidePlayBackground() {
        if (mRlytPlayBackground != null) {
            mRlytPlayBackground.setVisibility(View.GONE);
        }
    }

    @Override
    protected void initPublishConfigs() {

    }

    @Override
    protected void initPlayConfigs(ViewLive viewLive, String streamID) {

    }

    @Override
    protected void sendRoomMessage() {
        doSendRoomMsg(mEdtMessage.getText().toString());
    }

    @Override
    protected void doPublish() {
        if (mIsPublishing) {
            stopPublish();
        } else {
            // 请求连麦
            requestJoinLive();
        }
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        handleConfigurationChanged(newConfig);
    }

    @Override
    protected void beforePublish() {
    }

    @Override
    protected void afterPublish() {

    }
}
