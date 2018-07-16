package com.zego.livedemo5.ui.activities;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.text.TextUtils;
import android.util.Log;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.zego.livedemo5.R;
import com.zego.livedemo5.constants.Constants;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.presenters.RoomInfo;
import com.zego.livedemo5.presenters.StreamInfo;
import com.zego.livedemo5.ui.widgets.ViewLive;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.livedemo5.utils.ZegoRoomUtil;
import com.zego.zegoliveroom.callback.IZegoResponseCallback;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Copyright © 2017 Zego. All rights reserved.
 */
public abstract class BasePlayActivity extends BaseLiveActivity {

    protected RelativeLayout mRlytPlayBackground = null;

    protected ArrayList<String> mOldSavedStreamList = null;

    /**
     * 推流前的工作.
     */
    protected abstract  void beforePublish();

    /**
     * 推流后的工作.
     */
    protected abstract void afterPublish();

    @Override
    protected void initExtraData(Bundle savedInstanceState) {
        if (savedInstanceState == null) {
            Intent intent = getIntent();
            mRoomID = intent.getStringExtra(IntentExtra.ROOM_ID);
            mOldSavedStreamList = intent.getStringArrayListExtra(IntentExtra.LIST_STREAM);
        }
        super.initExtraData(savedInstanceState);
    }

    @Override
    protected void initViews(Bundle savedInstanceState) {
        super.initViews(savedInstanceState);

        mRlytPlayBackground = (RelativeLayout) getLayoutInflater().inflate(R.layout.view_play_bg, null);
        mRlytPlayBackground.setLayoutParams(mListViewLive.get(0).getLayoutParams());
        ((RelativeLayout) mListViewLive.get(0).getParent()).addView(mRlytPlayBackground);
    }

    static protected ArrayList<String> getStremListFromRoomInfo(RoomInfo roomInfo) {
        ArrayList<String> streamList = null;
        if (roomInfo.stream_info != null && roomInfo.stream_info.size() > 0) {
            streamList = new ArrayList<>(roomInfo.stream_info.size());
            for (StreamInfo stream : roomInfo.stream_info) {
                streamList.add(stream.stream_id);
            }
        }
        return streamList;
    }

    /**
     * 观众登录房间成功.
     */
    protected void handleAudienceLoginRoomSuccess(ZegoStreamInfo[] zegoStreamInfos) {
        // 播放房间的流
        if (zegoStreamInfos != null && zegoStreamInfos.length > 0) {
            for (int i = 0; i < zegoStreamInfos.length; i++) {
                String streamId = zegoStreamInfos[i].streamID;
                if (mOldSavedStreamList != null && mOldSavedStreamList.contains(streamId)) {
                    Log.w("BasePlayAct", "Has quick start, ignore");
                    mOldSavedStreamList.remove(streamId);
                } else {
                    startPlay(streamId);
                }
            }

            if (mOldSavedStreamList != null && mOldSavedStreamList.size() > 0) {
                for (String streamId : mOldSavedStreamList) {
                    Log.w("BasePlayAct", "Remove timeout stream id: " + streamId);
                    stopPlay(streamId);
                }
                mOldSavedStreamList.clear();
            }
        }

        // 分享主播视频
        if (zegoStreamInfos != null && zegoStreamInfos.length > 0) {
            for (ZegoStreamInfo info : zegoStreamInfos) {

                ViewLive viewLive = getViewLiveByStreamID(info.streamID);
                final HashMap<String, String> mapInfo =
                        (new Gson()).fromJson(info.extraInfo, new TypeToken<HashMap<String, String>>() {
                        }.getType());

                if (viewLive != null && mapInfo != null) {
                    boolean firstAnchor = Boolean.valueOf(mapInfo.get(Constants.FIRST_ANCHOR));
                    if (firstAnchor) {
                        List<String> listUrls = new ArrayList<>();
                        listUrls.add(mapInfo.get(Constants.KEY_HLS));
                        listUrls.add(mapInfo.get(Constants.KEY_RTMP));
                        viewLive.setListShareUrls(listUrls);
                        break;
                    }

                }
            }
        }

        // 打印log
        recordLog(MY_SELF + ": onLoginRoom success(" + mRoomID + "), streamCounts:" + zegoStreamInfos.length);
    }

    /**
     * 观众登录房间成功, 混流模式.
     */
    protected void handleAudienceLoginRoomSuccessMix(ZegoStreamInfo[] zegoStreamInfos) {

        if (zegoStreamInfos != null && zegoStreamInfos.length > 0) {
            for (ZegoStreamInfo info : zegoStreamInfos) {
                mListStreamOfRoom.add(info);
            }

            for (ZegoStreamInfo info : zegoStreamInfos) {
                final HashMap<String, String> mapExtraInfo =
                        (new Gson()).fromJson(info.extraInfo, new TypeToken<HashMap<String, String>>() {
                        }.getType());

                if (mapExtraInfo != null && mapExtraInfo.size() > 0) {

                    boolean firstAnchor = Boolean.valueOf(mapExtraInfo.get(Constants.FIRST_ANCHOR));
                    String mixStreamID = String.valueOf(mapExtraInfo.get(Constants.KEY_MIX_STREAM_ID));
                    if (firstAnchor && !TextUtils.isEmpty(mixStreamID)) {
                        // 播放混流
                        mMixStreamID = mixStreamID;
                        startPlay(mixStreamID);

                        // 设置分享地址
                        ViewLive viewLive = getViewLiveByStreamID(mixStreamID);
                        List<String> listUrls = new ArrayList<>();
                        listUrls.add(mapExtraInfo.get(Constants.KEY_HLS));
                        listUrls.add(mapExtraInfo.get(Constants.KEY_RTMP));
                        viewLive.setListShareUrls(listUrls);
                        break;
                    }
                }
            }
        }

        // 打印log
        recordLog(MY_SELF + ": onLoginRoom success(" + mRoomID + "), streamCounts:" + zegoStreamInfos.length);
    }


    /**
     * 观众登录房间失败.
     */
    protected void handleAudienceLoginRoomFail(int errorCode) {
        // 打印log
        recordLog(MY_SELF + ": onLoginRoom fail(" + mRoomID + ") errorCode:" + errorCode);
    }

    /**
     * 请求连麦.
     */
    protected void requestJoinLive() {
        mTvPublisnControl.setEnabled(false);
        mZegoLiveRoom.requestJoinLive(new IZegoResponseCallback() {
            @Override
            public void onResponse(int result, String fromUserID, String fromUserName) {
                if (result == ZegoConstants.ResultCode.YES) {

                    // 连麦请求被通过
                    recordLog(getString(R.string.request_of_broadcast_has_been_allowed, MY_SELF));
                    if(mPublishStreamID!= null && isStreamExisted(mPublishStreamID)){
                        Toast.makeText(getApplicationContext(),"当前已经是连麦状态",Toast.LENGTH_LONG).show();
                       return;
                    }
                    // 推流前
                    beforePublish();

                    mPublishTitle = PreferenceUtil.getInstance().getUserName() + " is coming";
                    mPublishStreamID = ZegoRoomUtil.getPublishStreamID();
                    // 推流前设置app朝向
                    setAppOrientation();
                    startPublish();

                    // 推流后
                    afterPublish();
                } else {
                    // 连麦请求被拒绝
                    recordLog(getString(R.string.request_of_broadcast_has_been_denied, MY_SELF));
                    AlertDialog dialogNotify = new AlertDialog.Builder(BasePlayActivity.this).setTitle(getString(R.string.hint))
                            .setMessage(getString(R.string.your_request_has_been_denied)).setPositiveButton(getString(R.string.got_it),
                                    new DialogInterface.OnClickListener() {
                                        @Override
                                        public void onClick(DialogInterface dialog, int which) {
                                            dialog.dismiss();
                                        }
                                    }).create();
                    dialogNotify.show();
                }
                mTvPublisnControl.setEnabled(true);
            }
        });
    }


    /**
     * 响应结束连麦信令
     * @param fromUserId
     * @param fromUserName
     * @param roomId
     */
    protected void handleEndJoinLiveCommand(String fromUserId, String fromUserName, String roomId) {
        recordLog("handleEndJoinLiveCommand, from userId: %s, from userName: %s, roomId: %s", fromUserId, fromUserName, roomId);
        stopPublish();
    }

    /**
     * 推流成功.
     */
    protected void handlePublishSucc(String streamID, HashMap<String, Object> info) {

        ViewLive viewLivePublish = getViewLiveByStreamID(streamID);
        List<String> listUrls = getShareUrlList(info);
        if (viewLivePublish != null && listUrls.size() >= 2) {
            // 设置分享连接
            viewLivePublish.setListShareUrls(listUrls);

            // 将流地址发送给房间观众
            Map<String, String> mapUrls = new HashMap<>();
            mapUrls.put(Constants.FIRST_ANCHOR, String.valueOf(false));
            mapUrls.put(Constants.KEY_HLS, listUrls.get(0));
            mapUrls.put(Constants.KEY_RTMP, listUrls.get(1));
            Gson gson = new Gson();
            String json = gson.toJson(mapUrls);
            mZegoLiveRoom.updateStreamExtraInfo(json);
        }


        super.handlePublishSucc(streamID);
    }

    /**
     * 推流成功_混流环境.
     */
    protected void handlePublishSuccMix(String streamID, HashMap<String, Object> info) {
        super.handlePublishSucc(streamID);
    }
}
