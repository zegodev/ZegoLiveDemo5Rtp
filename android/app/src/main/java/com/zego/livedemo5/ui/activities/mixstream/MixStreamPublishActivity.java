package com.zego.livedemo5.ui.activities.mixstream;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.google.gson.Gson;
import com.zego.livedemo5.R;
import com.zego.livedemo5.ZegoApiManager;
import com.zego.livedemo5.constants.Constants;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.ui.activities.BasePublishActivity;
import com.zego.livedemo5.ui.widgets.ViewLive;
import com.zego.livedemo5.utils.ZegoRoomUtil;
import com.zego.zegoavkit2.mixstream.IZegoMixStreamCallback;
import com.zego.zegoavkit2.mixstream.ZegoCompleteMixStreamInfo;
import com.zego.zegoavkit2.mixstream.ZegoMixStreamInfo;
import com.zego.zegoavkit2.mixstream.ZegoStreamMixer;
import com.zego.zegoliveroom.callback.IZegoLivePlayerCallback;
import com.zego.zegoliveroom.callback.IZegoLivePublisherCallback;
import com.zego.zegoliveroom.callback.IZegoLoginCompletionCallback;
import com.zego.zegoliveroom.callback.IZegoRoomCallback;
import com.zego.zegoliveroom.callback.im.IZegoIMCallback;
import com.zego.zegoliveroom.constants.ZegoAvConfig;
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
import java.util.List;
import java.util.Map;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class MixStreamPublishActivity extends BasePublishActivity {

    protected List<ZegoMixStreamInfo> mMixStreamInfos = new ArrayList<>();

    private ZegoStreamMixer mStreamMixer = new ZegoStreamMixer();

    /**
     * 启动入口.
     *
     * @param activity     源activity
     * @param publishTitle 视频标题
     */
    public static void actionStart(Activity activity, String publishTitle, boolean enableFrontCam, boolean enableTorch, int selectedBeauty, int selectedFilter, int appOrientation) {
        Intent intent = new Intent(activity, MixStreamPublishActivity.class);
        intent.putExtra(IntentExtra.PUBLISH_TITLE, publishTitle);
        intent.putExtra(IntentExtra.ENABLE_FRONT_CAM, enableFrontCam);
        intent.putExtra(IntentExtra.ENABLE_TORCH, enableTorch);
        intent.putExtra(IntentExtra.SELECTED_BEAUTY, selectedBeauty);
        intent.putExtra(IntentExtra.SELECTED_FILTER, selectedFilter);
        intent.putExtra(IntentExtra.APP_ORIENTATION, appOrientation);
        activity.startActivity(intent);
    }


    @Override
    protected void initViews(Bundle savedInstanceState) {
        super.initViews(savedInstanceState);
    }

    @Override
    protected void doBusiness(Bundle savedInstanceState) {
        super.doBusiness(savedInstanceState);
        mRoomID = ZegoRoomUtil.getRoomID(ZegoRoomUtil.ROOM_TYPE_MIX);
        mZegoLiveRoom.setRoomConfig(false, true);
        // 登录房间
        mZegoLiveRoom.loginRoom(mRoomID, mPublishTitle, ZegoConstants.RoomRole.Anchor, new IZegoLoginCompletionCallback() {
            @Override
            public void onLoginCompletion(int errorCode, ZegoStreamInfo[] zegoStreamInfos) {
                if (errorCode == 0) {
                    handleAnchorLoginRoomSuccess(zegoStreamInfos);
                } else {
                    handleAnchorLoginRoomFail(errorCode);
                }
            }
        });

        // 主播回调
        mZegoLiveRoom.setZegoLivePublisherCallback(new IZegoLivePublisherCallback() {
            @Override
            public void onPublishStateUpdate(int stateCode, String streamID, HashMap<String, Object> streamInfo) {
                //按钮允许点击
                setEnabled(true);
                //推流状态更新
                if (stateCode == 0) {
                    handlePublishSuccMix(streamID, streamInfo);
                } else {
                    handlePublishStop(stateCode, streamID);
                }
            }

            @Override
            public void onJoinLiveRequest(final int seq, String fromUserID, String fromUserName, String roomID) {
                // 有人请求连麦
                handleJoinLiveRequest(seq, fromUserID, fromUserName, roomID);
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
            public void onCaptureVideoSizeChangedTo(int width, int height) {

            }

            @Override
            public void onMixStreamConfigUpdate(int errorCode, String mixStreamID, HashMap<String, Object> streamInfo) {
                handleMixStreamStateUpdate(errorCode, mixStreamID, streamInfo);
            }
        });

        // 观众回调
        mZegoLiveRoom.setZegoLivePlayerCallback(new IZegoLivePlayerCallback() {
            @Override
            public void onPlayStateUpdate(int stateCode, String streamID) {
                // 拉流状态更新

                if (stateCode == 0) {
                    handlePlaySucc(streamID);
                } else {
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
                            handleMixStreamAdded(listStream, roomID);
                            break;
                        case ZegoConstants.StreamUpdateType.Deleted:
                            handleMixStreamDeleted(listStream, roomID);
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

        mStreamMixer.setCallback(new IZegoMixStreamCallback() {
            @Override
            public void onMixStreamConfigUpdate(int i, String s, HashMap<String, Object> hashMap) {
                handleMixStreamStateUpdate(i,s,hashMap);
            }
        });
    }

    @Override
    protected void handlePublishSuccMix(String streamID, HashMap<String, Object> info) {
        super.handlePublishSucc(streamID);
        final int margin = 25;
        ZegoMixStreamInfo mixStreamInfo = new ZegoMixStreamInfo();
        mixStreamInfo.streamID = mPublishStreamID;
        mixStreamInfo.top = 0 + margin;
        mixStreamInfo.bottom = ZegoApiManager.getInstance().getZegoAvConfig().getVideoEncodeResolutionHeight() - margin;
        mixStreamInfo.left = 0 + margin;
        mixStreamInfo.right = ZegoApiManager.getInstance().getZegoAvConfig().getVideoEncodeResolutionWidth() - margin;
        mMixStreamInfos.add(mixStreamInfo);

        startMixStream();
    }

    /**
     * 房间内用户创建流.
     */
    protected void handleMixStreamAdded(final ZegoStreamInfo[] listStream, final String roomID) {
        ZegoAvConfig zegoAvConfig = ZegoApiManager.getInstance().getZegoAvConfig();

        int width = zegoAvConfig.getVideoEncodeResolutionWidth();
        int height = zegoAvConfig.getVideoEncodeResolutionHeight();
        if (listStream != null && listStream.length > 0) {
            for (ZegoStreamInfo streamInfo : listStream) {
                recordLog(streamInfo.userName + ": onStreamAdd(" + streamInfo.streamID + ")");
                startPlay(streamInfo.streamID);

                if (mMixStreamInfos.size() == 1) {
                    ZegoMixStreamInfo mixStreamInfo = new ZegoMixStreamInfo();
                    mixStreamInfo.streamID = streamInfo.streamID;
                    mixStreamInfo.top = (int) (height * 2.0 / 3);
                    mixStreamInfo.bottom = height;
                    mixStreamInfo.left = (int) (width * 2.0 / 3);
                    mixStreamInfo.right = width;
                    mMixStreamInfos.add(mixStreamInfo);

                } else if (mMixStreamInfos.size() == 2) {
                    ZegoMixStreamInfo mixStreamInfo = new ZegoMixStreamInfo();
                    mixStreamInfo.streamID = streamInfo.streamID;
                    mixStreamInfo.top = (int) (height * 2.0 / 3);
                    mixStreamInfo.bottom = height;
                    mixStreamInfo.left = (int) (width * 1.0 / 3) - 10;
                    mixStreamInfo.right = (int) (width * 2.0 / 3) - 10;
                    mMixStreamInfos.add(mixStreamInfo);
                }
            }

            startMixStream();
        }
    }

    /**
     * 房间内用户删除流.
     */
    protected void handleMixStreamDeleted(final ZegoStreamInfo[] listStream, final String roomID) {
        if (listStream != null && listStream.length > 0) {
            for (ZegoStreamInfo bizStream : listStream) {
                recordLog(bizStream.userName + ": onStreamDelete(" + bizStream.streamID + ")");
                stopPlay(bizStream.streamID);

                for (ZegoMixStreamInfo info : mMixStreamInfos) {
                    if (bizStream.streamID.equals(info.streamID)) {
                        mMixStreamInfos.remove(info);
                        break;
                    }
                }
            }

            startMixStream();
        }
    }

    private int mixStreamRequestSeq = 1;
    private void startMixStream() {
        int size = mMixStreamInfos.size();
        ZegoMixStreamInfo[] inputStreamList = new ZegoMixStreamInfo[size];

        for (int i = 0; i < size; i++) {
            inputStreamList[i] = mMixStreamInfos.get(i);
        }
        ZegoCompleteMixStreamInfo mixStreamConfig = new ZegoCompleteMixStreamInfo();
        mixStreamConfig.inputStreamList = inputStreamList;
        mixStreamConfig.outputStreamId = mMixStreamID;
        mixStreamConfig.outputIsUrl = false;
        mixStreamConfig.outputWidth = ZegoApiManager.getInstance().getZegoAvConfig().getVideoCaptureResolutionWidth();
        mixStreamConfig.outputHeight = ZegoApiManager.getInstance().getZegoAvConfig().getVideoCaptureResolutionHeight();
        mixStreamConfig.outputFps = 15;
        mixStreamConfig.outputBitrate = 600 * 1000;
        mixStreamConfig.outputBackgroundColor = 0xc8c8c800;
//        mZegoLiveRoom.mixStream(mixStreamConfig, mixStreamRequestSeq++);

        mStreamMixer.mixStream(mixStreamConfig, mixStreamRequestSeq++);

    }

    protected void handleMixStreamStateUpdate(int errorCode, String mixStreamID, HashMap<String, Object> streamInfo) {
        int seq = -1;
        if (streamInfo != null) {
            seq = (int)streamInfo.get(ZegoConstants.StreamKey.MIX_CONFIG_SEQ);
        }
        if (errorCode == 0) {

            ViewLive viewLivePublish = getViewLiveByStreamID(mPublishStreamID);
            List<String> listUrls = getShareUrlList(streamInfo);

            if(listUrls.size() == 0){
                recordLog("混流失败...errorCode: %d, seq: %d", errorCode, seq);
            }else{
                recordLog("混流成功 地址: %s; seq: %d", listUrls.get(0), seq);
            }

            if(viewLivePublish != null && listUrls.size() >= 2){
                recordLog("混流地址: %s; seq: %d", listUrls.get(1), seq);
                viewLivePublish.setListShareUrls(listUrls);

                // 将混流ID通知观众
                Map<String, String> mapUrls = new HashMap<>();
                mapUrls.put(Constants.FIRST_ANCHOR, String.valueOf(true));
                mapUrls.put(Constants.KEY_MIX_STREAM_ID, mixStreamID);
                mapUrls.put(Constants.KEY_HLS, listUrls.get(0));
                mapUrls.put(Constants.KEY_RTMP, listUrls.get(1));

                Gson gson = new Gson();
                String json = gson.toJson(mapUrls);
                mZegoLiveRoom.updateStreamExtraInfo(json);
            }
        } else {
            recordLog("混流失败...errorCode: %d, seq: %d", errorCode, seq);
        }

        mRlytControlHeader.bringToFront();
    }


    @Override
    protected void initPublishControlText() {
        if (mIsPublishing) {
            mTvPublisnControl.setText(R.string.stop_publishing);
            mTvPublishSetting.setEnabled(true);

            mRlytControlHeader.bringToFront();
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
        mMixStreamInfos.clear();
        // 混流模式
        mPublishFlag = ZegoConstants.PublishFlag.MixStream;
        mMixStreamID = "mix-" + mPublishStreamID;
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
            startPublish();
        }
    }

}
