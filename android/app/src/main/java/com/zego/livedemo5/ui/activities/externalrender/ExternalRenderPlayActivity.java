package com.zego.livedemo5.ui.activities.externalrender;

import android.app.Activity;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.RelativeLayout;

import com.zego.livedemo5.R;
import com.zego.livedemo5.ZegoApiManager;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.presenters.RoomInfo;
import com.zego.livedemo5.ui.activities.BasePlayActivity;
import com.zego.livedemo5.ui.widgets.ViewLive;
import com.zego.zegoliveroom.callback.IZegoLivePlayerCallback;
import com.zego.zegoliveroom.callback.IZegoLoginCompletionCallback;
import com.zego.zegoliveroom.callback.IZegoRoomCallback;
import com.zego.zegoliveroom.callback.im.IZegoRoomMessageCallback;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.constants.ZegoIM;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;
import com.zego.zegoliveroom.entity.ZegoStreamQuality;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class ExternalRenderPlayActivity extends BasePlayActivity {

    /**
     * 启动入口.
     *
     * @param activity 源activity
     * @param roomInfo 房间信息
     */
    public static void actionStart(Activity activity, RoomInfo roomInfo) {
        Intent intent = new Intent(activity, ExternalRenderPlayActivity.class);
        intent.putExtra(IntentExtra.ROOM_ID, roomInfo.room_id);
        activity.startActivity(intent);
        activity.overridePendingTransition(R.anim.scale_translate,
                R.anim.my_alpha_action);
    }

    @Override
    protected void initExtraData(Bundle savedInstanceState) {
        if (savedInstanceState == null) {
            Intent intent = getIntent();
            mRoomID = intent.getStringExtra(IntentExtra.ROOM_ID);
        }
        super.initExtraData(savedInstanceState);
    }

    @Override
    protected void initViews(Bundle savedInstanceState) {
        super.initViews(savedInstanceState);

        // 提示用户, 当前正处于外部滤镜
        if (ZegoApiManager.getInstance().isUseExternalRender()) {
            mTvTag.setVisibility(View.VISIBLE);
            mTvTag.setText(getString(R.string.external_render));
        }

        mRlytPlayBackground.setVisibility(View.GONE);
    }

    @Override
    protected void doBusiness(Bundle savedInstanceState) {
        super.doBusiness(savedInstanceState);
        mZegoLiveRoom.loginRoom(mRoomID, ZegoConstants.RoomRole.Audience, new IZegoLoginCompletionCallback() {
            @Override
            public void onLoginCompletion(int errorCode, ZegoStreamInfo[] zegoStreamInfos) {
                if (errorCode == 0) {
                    handleAudienceLoginRoomSuccess(zegoStreamInfos);
                } else {
                    handleAudienceLoginRoomFail(errorCode);
                }
            }
        });

        mZegoLiveRoom.setZegoLivePlayerCallback(new IZegoLivePlayerCallback() {
            @Override
            public void onPlayStateUpdate(int stateCode, String streamID) {
                // 拉流状态更新
                if (stateCode == 0) {
                    handlePlaySucc(streamID);
                } else {
                    handlePlayStop(stateCode, streamID);
                }

                // 禁止连麦按钮
                mTvPublisnControl.setEnabled(false);
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
    }

    @Override
    protected void initPublishControlText() {
        mTvPublisnControl.setText(R.string.request_to_join);
        mTvPublishSetting.setEnabled(false);
        mTvPublisnControl.setEnabled(false);
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
        // 开启外部渲染
        VideoRenderer videoRenderer = new VideoRenderer();
        videoRenderer.init();
        videoRenderer.setRendererView(viewLive.getTextureView());
        mZegoLiveRoom.setZegoExternalRenderCallback(videoRenderer);
        recordLog(MY_SELF + ": 开启外部渲染 " + streamID);
    }

    @Override
    protected void sendRoomMessage() {
        String msg = mEdtMessage.getText().toString();
        if (!TextUtils.isEmpty(msg)) {
            mZegoLiveRoom.sendRoomMessage(ZegoIM.MessageType.Text, ZegoIM.MessageCategory.Chat, ZegoIM.MessagePriority.Default, msg, new IZegoRoomMessageCallback() {
                @Override
                public void onSendRoomMessage(int errorCode, String roomID, long messageID) {
                    if (errorCode == 0) {
                        recordLog(MY_SELF + ": 发送房间消息成功, roomID:" + roomID);
                    } else {
                        recordLog(MY_SELF + ": 发送房间消息失败, roomID:" + roomID + ", messageID:" + messageID);
                    }
                }
            });
        }
    }

    @Override
    protected void doPublish() {
    }

    @Override
    protected void beforePublish() {

    }

    @Override
    protected void afterPublish() {

    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);
        handleConfigurationChanged(newConfig);
    }
}
