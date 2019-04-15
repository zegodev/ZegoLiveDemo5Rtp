package com.zego.livedemo5.ui.activities.singleanchor;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.zego.livedemo5.R;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.ui.activities.BasePublishActivity;
import com.zego.livedemo5.ui.widgets.ViewLive;
import com.zego.livedemo5.utils.ZegoRoomUtil;
import com.zego.zegoliveroom.callback.IZegoAudioPrepCallback;
import com.zego.zegoliveroom.callback.IZegoLivePublisherCallback;
import com.zego.zegoliveroom.callback.IZegoLoginCompletionCallback;
import com.zego.zegoliveroom.callback.IZegoRoomCallback;
import com.zego.zegoliveroom.callback.im.IZegoIMCallback;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.entity.AuxData;
import com.zego.zegoliveroom.entity.ZegoBigRoomMessage;
import com.zego.zegoliveroom.entity.ZegoConversationMessage;
import com.zego.zegoliveroom.entity.ZegoPublishStreamQuality;
import com.zego.zegoliveroom.entity.ZegoRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;
import com.zego.zegoliveroom.entity.ZegoUserState;

import java.nio.ByteBuffer;
import java.util.HashMap;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class SingleAnchorPublishActivity extends BasePublishActivity {

    /**
     * 启动入口.
     *
     * @param activity     源activity
     * @param publishTitle 视频标题
     */
    public static void actionStart(Activity activity, String publishTitle, boolean enableFrontCam, boolean enableTorch, int selectedBeauty, int selectedFilter, int appOrientation) {
        Intent intent = new Intent(activity, SingleAnchorPublishActivity.class);
        intent.putExtra(IntentExtra.PUBLISH_TITLE, publishTitle);
        intent.putExtra(IntentExtra.ENABLE_FRONT_CAM, enableFrontCam);
        intent.putExtra(IntentExtra.ENABLE_TORCH, enableTorch);
        intent.putExtra(IntentExtra.SELECTED_BEAUTY, selectedBeauty);
        intent.putExtra(IntentExtra.SELECTED_FILTER, selectedFilter);
        intent.putExtra(IntentExtra.APP_ORIENTATION, appOrientation);
        activity.startActivity(intent);
    }


    @Override
    protected void doBusiness(Bundle savedInstanceState) {
        super.doBusiness(savedInstanceState);
        mRoomID = ZegoRoomUtil.getRoomID(ZegoRoomUtil.ROOM_TYPE_SINGLE);
        mZegoLiveRoom.setRoomConfig(false, true);
        mZegoLiveRoom.loginRoom(mRoomID, mPublishTitle, ZegoConstants.RoomRole.Anchor, new IZegoLoginCompletionCallback() {
            @Override
            public void onLoginCompletion(int errorCode, ZegoStreamInfo[] zegoStreamInfos) {
                if(errorCode == 0){
                    handleAnchorLoginRoomSuccess(zegoStreamInfos);
                }else {
                    handleAnchorLoginRoomFail(errorCode);
                }
            }
        });

        mZegoLiveRoom.setZegoLivePublisherCallback(new IZegoLivePublisherCallback() {
            @Override
            public void onPublishStateUpdate(int stateCode, String streamID, HashMap<String, Object> streamInfo) {
                //按钮允许点击
                setEnabled(true);
                //推流状态更新
                if (stateCode == 0) {
                    handlePublishSucc(streamID, streamInfo);
                } else {
                    handlePublishStop(stateCode, streamID);
                }
            }

            @Override
            public void onJoinLiveRequest(final int seq, String fromUserID, String fromUserName, String roomID) {
            }

            @Override
            public void onPublishQualityUpdate(String streamID, ZegoPublishStreamQuality streamQuality) {
                handlePublishQualityUpdate(streamID, streamQuality.quality, streamQuality.vnetFps, streamQuality.vkbps);
            }

            @Override
            public AuxData onAuxCallback(int dataLen) {
                return handleAuxCallback(dataLen);
            }

            @Override
            public void onCaptureVideoSizeChangedTo(int width, int height) {

            }

            @Override
            public void onMixStreamConfigUpdate(int errorCode, String streamID, HashMap<String, Object> streamInfo) {

            }

            @Override
            public void onCaptureVideoFirstFrame() {

            }
        });

        mZegoLiveRoom.setZegoRoomCallback(new IZegoRoomCallback() {
            @Override
            public void onKickOut(int reason, String roomID) {

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
                if (listStream != null && listStream.length > 0) {
                    switch (type) {
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
            public void onStreamExtraInfoUpdated(ZegoStreamInfo[] zegoStreamInfos, String s) {

            }

            @Override
            public void onRecvCustomCommand(String userID, String userName, String content, String roomID) {

            }
        });

        mZegoLiveRoom.setZegoIMCallback(new IZegoIMCallback() {

            @Override
            public void onUserUpdate(ZegoUserState[] listUser, int updateType) {
                handleUserUpdate(listUser, updateType);
            }

            @Override
            public void onRecvRoomMessage(String roomID, ZegoRoomMessage[] listMsg) {
                handleRecvRoomMsg(roomID, listMsg);
            }

            @Override
            public void onRecvConversationMessage(String roomID, String conversationID, ZegoConversationMessage message) {
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

        mZegoLiveRoom.setZegoAudioPrepCallback(new IZegoAudioPrepCallback() {
            @Override
            public void onAudioPrep(ByteBuffer inData, int sampleCount, int bitDepth, int sampleRate, ByteBuffer outData) {
                if(inData != null && outData != null){
                    inData.position(0);
                    outData.position(0);
                    // outData的长度固定为sampleCount * bitDepth
                    // 不可更改
                    outData.limit(sampleCount * bitDepth);
                    // 将处理后的数据返回sdk
                    outData.put(inData);
                }
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    protected void initPublishControlText() {
        if (mIsPublishing) {
            mTvPublisnControl.setText(R.string.stop_publishing);
            mTvPublishSetting.setEnabled(true);
        } else {
            mTvPublisnControl.setText(R.string.start_publishing);
            mTvPublishSetting.setEnabled(false);
        }
    }

    @Override
    protected void hidePlayBackground() {
    }

    @Override
    protected void initPublishConfigs() {
        // 单主播模式, 直推CDN
        mPublishFlag = ZegoConstants.PublishFlag.SingleAnchor;
    }

    @Override
    protected void initPlayConfigs(ViewLive viewLive, String streamID) {
    }

    @Override
    protected void sendRoomMessage() {
        doSendRoomMsg(mTvMessage.getText().toString());
    }

    @Override
    protected void doPublish() {
        if (mIsPublishing) {
            stopPublish();
        } else {
            startPublish();
        }
    }
}
