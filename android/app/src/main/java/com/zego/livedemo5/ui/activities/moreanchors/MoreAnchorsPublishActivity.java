package com.zego.livedemo5.ui.activities.moreanchors;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Rect;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.zego.livedemo5.R;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.ui.activities.BasePublishActivity;
import com.zego.livedemo5.ui.widgets.ViewLive;
import com.zego.livedemo5.utils.ZegoRoomUtil;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.callback.IZegoLivePlayerCallback;
import com.zego.zegoliveroom.callback.IZegoLivePublisherCallback;
import com.zego.zegoliveroom.callback.IZegoLivePublisherCallback2;
import com.zego.zegoliveroom.callback.IZegoLoginCompletionCallback;
import com.zego.zegoliveroom.callback.IZegoRoomCallback;
import com.zego.zegoliveroom.callback.IZegoSnapshotCompletionCallback2;
import com.zego.zegoliveroom.callback.im.IZegoIMCallback;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.constants.ZegoVideoViewMode;
import com.zego.zegoliveroom.entity.AuxData;
import com.zego.zegoliveroom.entity.ZegoBigRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamQuality;
import com.zego.zegoliveroom.entity.ZegoConversationMessage;
import com.zego.zegoliveroom.entity.ZegoRoomMessage;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;
import com.zego.zegoliveroom.entity.ZegoUserState;

import java.util.HashMap;


/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class MoreAnchorsPublishActivity extends BasePublishActivity {

    public static final String TAG_LOG = "MoreAnchorsPublishActivity";

    public static final String TAG_AUX = "Aux-";
    public static final int AUX_CHANNEL_INDEX = ZegoConstants.PublishChannelIndex.AUX;

    private TextView mTvAuxPublish;
    private String mAuxPublishStreamID = null;
    private boolean mIsAuxPublishing = false;

    /**
     * 启动入口.
     *
     * @param activity     源activity
     * @param publishTitle 视频标题
     */
    public static void actionStart(Activity activity, String publishTitle, boolean enableFrontCam, boolean enableTorch, int selectedBeauty, int selectedFilter, int appOrientation) {
        Intent intent = new Intent(activity, MoreAnchorsPublishActivity.class);
        intent.putExtra(IntentExtra.PUBLISH_TITLE, publishTitle);
        intent.putExtra(IntentExtra.ENABLE_FRONT_CAM, enableFrontCam);
        intent.putExtra(IntentExtra.ENABLE_TORCH, enableTorch);
        intent.putExtra(IntentExtra.SELECTED_BEAUTY, selectedBeauty);
        intent.putExtra(IntentExtra.SELECTED_FILTER, selectedFilter);
        intent.putExtra(IntentExtra.APP_ORIENTATION, appOrientation);
        activity.startActivity(intent);
    }

    private void publishAuxStream(int channelIndex){
        ViewLive freeViewLive = getFreeViewLive();
        if (freeViewLive == null) {
            return;
        }

        // 设置流信息
        freeViewLive.setStreamID(mAuxPublishStreamID);
        freeViewLive.setPublishView(true);

        // 初始化配置信息, 混流模式使用
        initPublishConfigs();

        // 输出发布状态
        recordLog(MY_SELF + ": start publishing(" + mAuxPublishStreamID + ")");

        // 设置水印
        ZegoLiveRoom.setWaterMarkImagePath("asset:watermark.png");
        Rect rect = new Rect();
        rect.left = 50;
        rect.top = 20;
        rect.right = 200;
        rect.bottom = 170;
        ZegoLiveRoom.setPreviewWaterMarkRect(rect, channelIndex);
        ZegoLiveRoom.setPublishWaterMarkRect(rect, channelIndex);

        // 开始播放
        mZegoLiveRoom.setPreviewView(freeViewLive.getTextureView(), channelIndex);
        mZegoLiveRoom.startPreview(channelIndex);
        mZegoLiveRoom.enableCamera(true, channelIndex);
        mZegoLiveRoom.setFrontCam(false, channelIndex);
        mZegoLiveRoom.startPublishing2(mAuxPublishStreamID, TAG_AUX + mPublishTitle, mPublishFlag, channelIndex);
        mZegoLiveRoom.setPreviewViewMode(ZegoVideoViewMode.ScaleAspectFill, channelIndex);

//        mZegoLiveRoom.setZegoLivePublisherCallback2(new IZegoLivePublisherCallback2() {
//            @Override
//            public void onCaptureVideoSizeChangedTo(int index, int width, int height) {
//                Log.i(TAG_LOG, "onCaptureVideoSizeChangedTo, index: " + index + ", width: " + width + ", height: " + height);
//            }
//        });
//
//        mZegoLiveRoom.takePreviewSnapshot(new IZegoSnapshotCompletionCallback2() {
//            @Override
//            public void onZegoSnapshotCompletion(int index, Bitmap bitmap) {
//                Log.i(TAG_LOG, "onZegoSnapshotCompletion, index: " + index + ", bitmap: " + bitmap);
//            }
//        }, AUX_CHANNEL_INDEX);
    }


    @Override
    protected void doBusiness(Bundle savedInstanceState) {
        super.doBusiness(savedInstanceState);

        mTvAuxPublish = (TextView) findViewById(R.id.tv_aux_publish);
        mTvAuxPublish.setVisibility(View.VISIBLE);
        mTvAuxPublish.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                if (!mIsAuxPublishing){
                    mIsAuxPublishing = true;
                    mTvAuxPublish.setEnabled(false);
                    mAuxPublishStreamID = TAG_AUX + mPublishStreamID;

                    publishAuxStream(AUX_CHANNEL_INDEX);

                }else{
                    mIsAuxPublishing = false;
                    mTvAuxPublish.setText(getString(R.string.start_aux_publish));

                    recordLog(MY_SELF + ": stop publishing(" + mAuxPublishStreamID + ")");
                    // 释放View
                    releaseLiveView(mAuxPublishStreamID);

                    mZegoLiveRoom.stopPreview(AUX_CHANNEL_INDEX);
                    mZegoLiveRoom.stopPublishing(AUX_CHANNEL_INDEX);
                    mZegoLiveRoom.setPreviewView(null, AUX_CHANNEL_INDEX);
                }
            }
        });

        mRoomID = ZegoRoomUtil.getRoomID(ZegoRoomUtil.ROOM_TYPE_MORE);

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
                if(stateCode == 0){
                    if (!TextUtils.isEmpty(streamID) && streamID.equals(mAuxPublishStreamID)){
                        mTvAuxPublish.setEnabled(true);
                        mTvAuxPublish.setText(getString(R.string.stop_aux_publish));
                    }
                    handlePublishSucc(streamID, streamInfo);
                }else {
                    if (!TextUtils.isEmpty(streamID) && streamID.equals(mAuxPublishStreamID)){
                        mTvAuxPublish.setText(R.string.start_aux_publish);
                    }
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
            public void onStreamExtraInfoUpdated(ZegoStreamInfo[] zegoStreamInfos, String s) {

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
        // 连麦模式
        mPublishFlag = ZegoConstants.PublishFlag.JoinPublish;
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
