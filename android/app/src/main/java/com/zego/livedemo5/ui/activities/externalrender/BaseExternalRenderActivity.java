package com.zego.livedemo5.ui.activities.externalrender;


import android.Manifest;
import android.app.Service;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.graphics.Rect;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.provider.Settings;
import android.support.design.widget.BottomSheetBehavior;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.telephony.PhoneStateListener;
import android.telephony.TelephonyManager;
import android.text.TextUtils;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.zego.livedemo5.R;
import com.zego.livedemo5.ZegoApiManager;
import com.zego.livedemo5.ui.activities.LogListActivity;
import com.zego.livedemo5.ui.activities.base.AbsBaseLiveActivity;
import com.zego.livedemo5.ui.widgets.PublishSettingsPannel;
import com.zego.livedemo5.ui.widgets.ViewLive;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.livedemo5.utils.ZegoRoomUtil;
import com.zego.zegoavkit2.ZegoMixEnginePlayout;
import com.zego.zegoavkit2.audioprocessing.ZegoAudioProcessing;
import com.zego.zegoavkit2.audioprocessing.ZegoAudioReverbMode;
import com.zego.zegoavkit2.camera.ZegoCamera;
import com.zego.zegoavkit2.camera.ZegoCameraExposureMode;
import com.zego.zegoavkit2.camera.ZegoCameraFocusMode;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.callback.IZegoResponseCallback;
import com.zego.zegoliveroom.constants.ZegoAvConfig;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.constants.ZegoVideoViewMode;
import com.zego.zegoliveroom.entity.AuxData;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import butterknife.OnClick;

/**
 * des: 主页面
 */
public abstract class BaseExternalRenderActivity extends AbsBaseLiveActivity {

    public static final String MY_SELF = "MySelf";

    protected InputStream mIsBackgroundMusic = null;

    protected LinkedList<ViewLive> mListViewLive = new LinkedList<>();

    protected LinkedList<String> mListLog = new LinkedList<>();

    protected Map<String, Boolean> mMapReplayStreamID = new HashMap<>();

    public TextView tvPublisnControl = null;

    public TextView tvPublishSetting = null;

    public TextView tvSpeaker = null;

    public TextView mTvTag = null;

    public BottomSheetBehavior mBehavior = null;

    public RelativeLayout mRlytControlHeader = null;

    protected String mPublishTitle = null;

    protected String mPublishStreamID = null;

    protected boolean mIsPublishing = false;

    protected boolean mEnableSpeaker = true;

    protected boolean mEnableCamera = true;

    protected boolean mEnableFrontCam = true;

    protected boolean mEnableMic = true;

    protected boolean mEnableTorch = false;

    protected boolean mEnableBackgroundMusic = false;

    protected boolean mEnableLoopback = false;

    protected boolean mEnableMixEngine = false;

    protected boolean mEnableVirtualStereo = false;

    protected boolean mEnableReverb = false;

    protected boolean mEnableCustomFocus = false;

    protected boolean mEnableCustomExposure = false;

    protected int mSelectedBeauty = 0;

    protected int mSelectedFilter = 0;

    protected int mLiveCount = 0;

    protected boolean mHostHasBeenCalled = false;

    protected ZegoLiveRoom mZegoLiveRoom = null;

    protected String mRoomID = null;

    protected PhoneStateListener mPhoneStateListener = null;

    protected PublishSettingsPannel mSettingsPannel= null;

    protected AlertDialog mDialogHandleRequestPublish = null;

    protected float[] mListExposureCompensation = {-1.0f, -0.9f, -0.8f, -0.7f, -0.6f, -0.5f, -0.4f, -0.3f, -0.2f, -0.1f, 0,
            0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f};

    protected abstract void initPublishControlText();

    protected abstract void hidePlayBackground();


    @Override
    protected int getContentViewLayout() {
        return R.layout.activity_live;
    }


    @Override
    protected void initExtraData(Bundle savedInstanceState) {
    }


    @Override
    protected void initVariables(final Bundle savedInstanceState) {
        mZegoLiveRoom = ZegoApiManager.getInstance().getZegoLiveRoom();
        // 初始化电话监听器
        initPhoneCallingListener();
    }

    /**
     * 初始化设置面板.
     */
    private void initSettingPannel() {

        mSettingsPannel = (PublishSettingsPannel) findViewById(R.id.publishSettingsPannel);
        mSettingsPannel.initPublishSettings(mEnableCamera, mEnableFrontCam, mEnableMic, mEnableTorch, mEnableBackgroundMusic, mEnableLoopback, mSelectedBeauty, mSelectedFilter, mEnableMixEngine, mEnableVirtualStereo, mEnableReverb, mEnableCustomFocus, mEnableCustomExposure);
        mSettingsPannel.setPublishSettingsCallback(new PublishSettingsPannel.PublishSettingsCallback() {
            @Override
            public void onEnableCamera(boolean isEnable) {
                mEnableCamera = isEnable;
                mZegoLiveRoom.enableCamera(isEnable);
            }

            @Override
            public void onEnableFrontCamera(boolean isEnable) {
                mEnableFrontCam = isEnable;
                mZegoLiveRoom.setFrontCam(isEnable);
            }

            @Override
            public void onEnableMic(boolean isEnable) {
                mEnableMic = isEnable;
                mZegoLiveRoom.enableMic(isEnable);
            }

            @Override
            public void onEnableTorch(boolean isEnable) {
                mEnableTorch = isEnable;
                mZegoLiveRoom.enableTorch(isEnable);
            }

            @Override
            public void onEnableBackgroundMusic(boolean isEnable) {
                mEnableBackgroundMusic = isEnable;
                mZegoLiveRoom.enableAux(isEnable);

                if (!isEnable) {
                    if (mIsBackgroundMusic != null) {
                        try {
                            mIsBackgroundMusic.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        mIsBackgroundMusic = null;
                    }
                }
            }

            @Override
            public void onEnableLoopback(boolean isEnable) {
                mEnableLoopback = isEnable;
                mZegoLiveRoom.enableLoopback(isEnable);
            }

            @Override
            public void onEnableMixEnginePlayout(boolean isEnable) {
                mEnableMixEngine = isEnable;
                ZegoMixEnginePlayout.mixEnginePlayout(isEnable);
            }

            @Override
            public void onEnableVirtualStereo(boolean isEnable) {
                mEnableVirtualStereo = isEnable;
                //hardcode angle = 0
                ZegoAudioProcessing.enableVirtualStereo(isEnable, 0);
            }

            @Override
            public void onEnableReverb(boolean isEnable) {
                mEnableReverb = isEnable;
                //hardcode reverbMode = ZegoAudioReverbMode.LARGE_AUDITORIUM
                ZegoAudioProcessing.enableReverb(isEnable, ZegoAudioReverbMode.LARGE_AUDITORIUM);
            }

            @Override
            public void onEnableCustomFocus(boolean isEnable) {
                recordLog(MY_SELF + ": call onEnableCustomFocus");
                mEnableCustomFocus = isEnable;
                if(!mEnableCustomFocus) {
                    ZegoCamera.setCamFocusMode(ZegoCameraFocusMode.CONTINUOUS_VIDEO, ZegoConstants.PublishChannelIndex.MAIN);
                }

            }

            @Override
            public void onEnableCustomExposure(boolean isEnable) {
                recordLog(MY_SELF + ": call onEnableCustomExposure");
                mEnableCustomExposure = isEnable;
                if(mEnableCustomFocus){
                    ZegoCamera.setCamExposureMode(ZegoCameraExposureMode.CUSTOM, ZegoConstants.PublishChannelIndex.MAIN);
                }
                else {
                    ZegoCamera.setCamExposureMode(ZegoCameraExposureMode.AUTO, ZegoConstants.PublishChannelIndex.MAIN);
                }
            }

            @Override
            public void onSetBeauty(int beauty) {
                mSelectedBeauty = beauty;
                mZegoLiveRoom.enableBeautifying(ZegoRoomUtil.getZegoBeauty(beauty));
            }

            @Override
            public void onSetFilter(int filter) {
                mSelectedFilter = filter;
                mZegoLiveRoom.setFilter(filter);
            }

            @Override
            public void onSetCustomExposureProgress(int progress) {
                ZegoCamera.setCamExposureCompensation(mListExposureCompensation[progress], ZegoConstants.PublishChannelIndex.MAIN);
            }
        });

        mBehavior = BottomSheetBehavior.from(mSettingsPannel);
        FrameLayout flytMainContent = (FrameLayout) findViewById(R.id.main_content);
        if (flytMainContent != null) {
            flytMainContent.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (mBehavior.getState() == BottomSheetBehavior.STATE_EXPANDED) {
                        mBehavior.setState(BottomSheetBehavior.STATE_COLLAPSED);
                    }
                }
            });
        }
    }

    @Override
    protected void initViews(Bundle savedInstanceState) {

        tvSpeaker = (TextView) findViewById(R.id.tv_speaker);
        tvPublishSetting = (TextView) findViewById(R.id.tv_publish_settings);
        tvPublisnControl = (TextView) findViewById(R.id.tv_publish_control);
        // 初始化推流控制按钮
        initPublishControlText();

        mRlytControlHeader = (RelativeLayout) findViewById(R.id.rlyt_control_header);

        initSettingPannel();

        final ViewLive vlBigView = (ViewLive) findViewById(R.id.vl_big_view);
        if (vlBigView != null) {
            vlBigView.setActivityHost(this);
            vlBigView.setZegoLiveRoom(mZegoLiveRoom);
            mListViewLive.add(vlBigView);
        }

        vlBigView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(!mEnableCustomFocus)
                    return false;

                switch(event.getAction())
                {
                    case MotionEvent.ACTION_DOWN:
                        List<Float> point = focusPointNormalize(event.getX(), event.getY());
                        ZegoCamera.setCamFocusPoint(point.get(0), point.get(1), ZegoConstants.PublishChannelIndex.MAIN);
                        ZegoCamera.setCamFocusMode(ZegoCameraFocusMode.AUTO, ZegoConstants.PublishChannelIndex.MAIN);
                        break;
                }

                return true;
            }
        });

        final ViewLive vlSmallView1 = (ViewLive) findViewById(R.id.vl_small_view1);
        if (vlSmallView1 != null) {
            vlSmallView1.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    vlSmallView1.toExchangeView(vlBigView);
                }
            });
            vlSmallView1.setActivityHost(this);
            vlSmallView1.setZegoLiveRoom(mZegoLiveRoom);
            mListViewLive.add(vlSmallView1);
        }


        final ViewLive vlSmallView2 = (ViewLive) findViewById(R.id.vl_small_view2);
        if (vlSmallView2 != null) {
            vlSmallView2.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    vlSmallView2.toExchangeView(vlBigView);
                }
            });
            vlSmallView2.setActivityHost(this);
            vlSmallView2.setZegoLiveRoom(mZegoLiveRoom);
            mListViewLive.add(vlSmallView2);
        }

        tvSpeaker.setSelected(!mEnableSpeaker);

        mTvTag = (TextView) findViewById(R.id.tv_tag);
    }

    @Override
    protected void doBusiness(Bundle savedInstanceState) {
    }

    @Override
    protected void onPause() {
        super.onPause();

        PreferenceUtil.getInstance().setObjectToString(LogListActivity.KEY_LIST_LOG, mListLog);
    }

    /**
     * 电话状态监听.
     */
    protected void initPhoneCallingListener() {
        mPhoneStateListener = new PhoneStateListener() {
            @Override
            public void onCallStateChanged(int state, String incomingNumber) {
                super.onCallStateChanged(state, incomingNumber);
                switch (state) {
                    case TelephonyManager.CALL_STATE_IDLE:
                        if (mHostHasBeenCalled) {
                            mHostHasBeenCalled = false;
                            recordLog(MY_SELF + ": call state idle");
                            // 登陆频道
                           for(ViewLive viewLive : mListViewLive){
                                if(viewLive.isPublishView()){
                                    startPublish();
                                }else if(viewLive.isPlayView()){
                                    startPlay(viewLive.getStreamID());
                                }
                           }
                        }

                        break;
                    case TelephonyManager.CALL_STATE_RINGING:
                        recordLog(MY_SELF + ": call state ringing");
                        mHostHasBeenCalled = true;
                        // 来电停止发布与播放
                        stopAllStream();
                        break;

                    case TelephonyManager.CALL_STATE_OFFHOOK:
                        break;
                }
            }
        };

        TelephonyManager tm = (TelephonyManager) getSystemService(Service.TELEPHONY_SERVICE);
        tm.listen(mPhoneStateListener, PhoneStateListener.LISTEN_CALL_STATE);
    }

    /**
     * 获取空闲的View用于播放或者发布.
     *
     * @return
     */
    protected ViewLive getFreeViewLive() {
        ViewLive vlFreeView = null;
        for (int i = 0, size = mListViewLive.size(); i < size; i++) {
            ViewLive viewLive = mListViewLive.get(i);
            if (viewLive.isFree()) {
                vlFreeView = viewLive;
                vlFreeView.setVisibility(View.VISIBLE);
                break;
            }
        }
        return vlFreeView;
    }

    /**
     * 释放View用于再次播放.
     *
     * @param streamID
     */
    protected void releaseLiveView(String streamID) {
        if(TextUtils.isEmpty(streamID)){
            return;
        }

        for (int i = 0, size = mListViewLive.size(); i < size; i++) {
            ViewLive currentViewLive = mListViewLive.get(i);
            if (streamID.equals(currentViewLive.getStreamID())) {
                int j = i;
                for (; j < size - 1; j++) {
                    ViewLive nextViewLive = mListViewLive.get(j + 1);
                    if (nextViewLive.isFree()) {
                        break;
                    }

                    if (nextViewLive.isPublishView()) {
                        mZegoLiveRoom.setPreviewView(currentViewLive.getTextureView());
                    } else {
                        mZegoLiveRoom.updatePlayView(nextViewLive.getStreamID(), currentViewLive.getTextureView());
                    }

                    currentViewLive.toExchangeView(nextViewLive);
                    currentViewLive = nextViewLive;
                }
                // 标记最后一个View可用
                mListViewLive.get(j).setFree();
                break;
            }
        }
    }

    /**
     * 通过streamID查找正在publish或者play的ViewLive.
     *
     * @param streamID
     * @return
     */
    protected ViewLive getViewLiveByStreamID(String streamID) {
        if (TextUtils.isEmpty(streamID)) {
            return null;
        }

        ViewLive viewLive = null;
        for (ViewLive vl : mListViewLive) {
            if (streamID.equals(vl.getStreamID())) {
                viewLive = vl;
                break;
            }
        }

        return viewLive;
    }

    protected void recordLog(String msg) {
        mListLog.addFirst(msg);
    }


    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case 101:
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED && grantResults[1] == PackageManager.PERMISSION_GRANTED) {
                    new Handler().post(new Runnable() {
                        @Override
                        public void run() {
                            publishStream(mPublishStreamID);
                        }
                    });
                } else {


                    if (grantResults[0] == PackageManager.PERMISSION_DENIED) {
                        Toast.makeText(this, R.string.allow_camera_permission, Toast.LENGTH_LONG).show();
                    }
                    if (grantResults[1] == PackageManager.PERMISSION_DENIED) {
                        Toast.makeText(this, R.string.open_recorder_permission, Toast.LENGTH_LONG).show();
                    }

                    Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
                    intent.setData(Uri.parse("package:" + getPackageName()));
                    startActivity(intent);
                }
                break;
        }
    }

    protected void publishStream(String streamID) {

        if (TextUtils.isEmpty(streamID)) {
            return;
        }

        ViewLive freeViewLive = getFreeViewLive();
        if (freeViewLive == null) {
            return;
        }

        // 设置流信息
        freeViewLive.setStreamID(streamID);
        freeViewLive.setPublishView(true);

        // 输出发布状态
        recordLog(MY_SELF + ": start publishing(" + streamID + ")");

        // 设置水印
        mZegoLiveRoom.setWaterMarkImagePath("asset:watermark.png");
        Rect rect = new Rect();
        rect.left = 50;
        rect.top = 20;
        rect.right = 200;
        rect.bottom = 170;
        mZegoLiveRoom.setPreviewWaterMarkRect(rect);
        mZegoLiveRoom.setPublishWaterMarkRect(rect);

        // 开启流量自动控制
        int properties = ZegoConstants.ZegoTrafficControlProperty.ZEGOAPI_TRAFFIC_FPS
                | ZegoConstants.ZegoTrafficControlProperty.ZEGOAPI_TRAFFIC_RESOLUTION;
        mZegoLiveRoom.enableTrafficControl(properties, true);

        // 开始播放
        mZegoLiveRoom.setPreviewView(freeViewLive.getTextureView());
        mZegoLiveRoom.startPreview();
        mZegoLiveRoom.startPublishing(mPublishStreamID, mPublishTitle, 0);
        mZegoLiveRoom.setPreviewViewMode(ZegoVideoViewMode.ScaleAspectFill);

    }

    /**
     * 开始发布.
     */
    protected void startPublish() {
        // 6.0及以上的系统需要在运行时申请CAMERA RECORD_AUDIO权限
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED
                    || ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(this, new String[]{
                        Manifest.permission.CAMERA, Manifest.permission.RECORD_AUDIO}, 101);
            } else {
                publishStream(mPublishStreamID);
            }
        } else {
            publishStream(mPublishStreamID);
        }
    }

    protected void stopPublish() {
        if (mIsPublishing) {
            // 临时处理
            handlePublishStop(1, mPublishStreamID);
            initPublishControlText();

            recordLog(MY_SELF + ": stop publishing(" + mPublishStreamID + ")");
            mZegoLiveRoom.stopPreview();
            mZegoLiveRoom.stopPublishing();
            mZegoLiveRoom.setPreviewView(null);
        }
    }

    protected void stopPlay(String streamID) {
        if (!TextUtils.isEmpty(streamID)) {
            // 临时处理
            handlePlayStop(1, streamID);

            // 输出播放状态
            recordLog(MY_SELF + ": stop play stream(" + streamID + ")");
            mZegoLiveRoom.stopPlayingStream(streamID);
        }
    }

    /**
     * 开始播放流.
     */
    protected void startPlay(String streamID) {

        if (TextUtils.isEmpty(streamID)) {
            return;
        }

        ViewLive freeViewLive = getFreeViewLive();
        if (freeViewLive == null) {
            return;
        }

        // 设置流信息
        freeViewLive.setStreamID(streamID);
        freeViewLive.setPlayView(true);

        // 输出播放状态
        recordLog(MY_SELF + ": start play stream(" + streamID + ")");

        // 开启外部渲染
        VideoRenderer videoRenderer = new VideoRenderer();
        videoRenderer.init();
        videoRenderer.setRendererView(freeViewLive.getTextureView());
        mZegoLiveRoom.setZegoExternalRenderCallback(videoRenderer);
        recordLog(MY_SELF + ": 开启外部渲染 " + streamID);

        // 播放
        mZegoLiveRoom.startPlayingStream(streamID, null);
        mZegoLiveRoom.setViewMode(ZegoVideoViewMode.ScaleAspectFill, streamID);
    }

    protected void logout() {

        mEnableFrontCam = true;
        mZegoLiveRoom.setFrontCam(mEnableFrontCam);

        mEnableLoopback = false;
        mZegoLiveRoom.enableLoopback(false);

        mEnableVirtualStereo = false;
        ZegoAudioProcessing.enableVirtualStereo(false, 0);

        mEnableReverb = false;
        ZegoAudioProcessing.enableReverb(false, ZegoAudioReverbMode.LARGE_AUDITORIUM);

        mEnableCustomFocus = false;
        ZegoCamera.setCamFocusMode(ZegoCameraFocusMode.CONTINUOUS_VIDEO, ZegoConstants.PublishChannelIndex.MAIN);

        mEnableCustomExposure = false;
        ZegoCamera.setCamExposureMode(ZegoCameraExposureMode.AUTO, ZegoConstants.PublishChannelIndex.MAIN);


        if (mIsPublishing) {
            AlertDialog dialog = new AlertDialog.Builder(this).setMessage(getString(R.string.do_you_really_want_to_leave)).setTitle(getString(R.string.hint)).setPositiveButton(getString(R.string.Yes), new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    stopAllStream();
                    dialog.dismiss();
                    finish();
                }
            }).setNegativeButton(getString(R.string.No), new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.dismiss();
                }
            }).create();

            dialog.show();
        } else {

            stopAllStream();
            finish();
        }

    }


    protected void stopAllStream() {
        for (ViewLive viewLive : mListViewLive) {
            if (viewLive.isPublishView()) {
                stopPublish();
            } else if (viewLive.isPlayView()) {
                stopPlay(viewLive.getStreamID());
            }
            // 释放view
            viewLive.setFree();
        }
    }

    protected void setPublishEnabled() {
        if(!mIsPublishing){
            if (mLiveCount < ZegoLiveRoom.getMaxPlayChannelCount() + 1) {
                tvPublisnControl.setEnabled(true);
            } else {
                tvPublisnControl.setEnabled(false);
            }
        }
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if (mBehavior.getState() == BottomSheetBehavior.STATE_EXPANDED) {
                mBehavior.setState(BottomSheetBehavior.STATE_COLLAPSED);
                return false;
            } else {
                // 退出
                logout();
            }

        }
        return super.onKeyDown(keyCode, event);
    }

    @OnClick(R.id.tv_log_list)
    public void openLogList() {
        LogListActivity.actionStart(this);
    }

    @OnClick(R.id.tv_publish_settings)
    public void publishSettings() {
        if (mBehavior.getState() == BottomSheetBehavior.STATE_COLLAPSED) {
            mBehavior.setState(BottomSheetBehavior.STATE_EXPANDED);
        } else {
            mBehavior.setState(BottomSheetBehavior.STATE_COLLAPSED);
        }
    }

    @OnClick(R.id.tv_speaker)
    public void doMute() {
        if (mEnableSpeaker) {
            mEnableSpeaker = false;
        } else {
            mEnableSpeaker = true;
        }

        mZegoLiveRoom.enableSpeaker(mEnableSpeaker);
        tvSpeaker.setSelected(!mEnableSpeaker);
    }

    @OnClick(R.id.tv_close)
    public void close() {
        logout();
    }

    /**
     * 推流成功.
     */
    protected void handlePublishSucc(String streamID, HashMap<String, Object> info) {
        mIsPublishing = true;
        recordLog(MY_SELF + ": onPublishSucc(" + streamID + ")");

        ViewLive viewLivePublish = getViewLiveByStreamID(streamID);
        if (viewLivePublish != null) {
            List<String> listUrls = new ArrayList<>();
            if (info != null) {

                String[] hlsList = (String[]) info.get("hlsList");
                if (hlsList != null && hlsList.length > 0) {
                    listUrls.add(hlsList[0]);
                }

                String[] rtmpList = (String[]) info.get("rtmpList");
                if (rtmpList != null && rtmpList.length > 0) {
                    listUrls.add(rtmpList[0]);
                }
            }
            viewLivePublish.setListShareUrls(listUrls);
        }

        initPublishControlText();
        mRlytControlHeader.bringToFront();
    }

    /**
     * 停止推流.
     */
    protected void handlePublishStop(int stateCode, String streamID) {
        mIsPublishing = false;
        recordLog(MY_SELF + ": onPublishStop(" + streamID + ") --stateCode:" + stateCode);

        // 释放View
        releaseLiveView(streamID);

        initPublishControlText();
        mRlytControlHeader.bringToFront();
    }

    /**
     * 推流质量更新.
     */
    protected void handlePublishQualityUpdate(String streamID, int quality, double videoFPS, double videoBitrate) {
        ViewLive viewLive = getViewLiveByStreamID(streamID);
        if (viewLive != null) {
            viewLive.setLiveQuality(quality, videoFPS, videoBitrate);
        }
    }

    protected AuxData handleAuxCallback(int dataLen) {
        // 开启伴奏后, sdk每20毫秒一次取数据
        if (!mEnableBackgroundMusic || dataLen <= 0) {
            return null;
        }

        AuxData auxData = new AuxData();
        auxData.dataBuf = new byte[dataLen];

        try {
            AssetManager am = getAssets();
            if (mIsBackgroundMusic == null) {
                mIsBackgroundMusic = am.open("a.pcm");
            }
            int len = mIsBackgroundMusic.read(auxData.dataBuf);

            if (len <= 0) {
                // 歌曲播放完毕
                mIsBackgroundMusic.close();
                mIsBackgroundMusic = null;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        auxData.channelCount = 2;
        auxData.sampleRate = 44100;


        return auxData;
    }

    /**
     * 拉流成功.
     */
    protected void handlePlaySucc(String streamID) {
        recordLog(MY_SELF + ": onPlaySucc(" + streamID + ")");

        mLiveCount++;
        setPublishEnabled();

        // 记录流ID用于play失败后重新play
        mMapReplayStreamID.put(streamID, false);

        mRlytControlHeader.bringToFront();
    }

    /**
     * 停止拉流.
     */
    protected void handlePlayStop(int stateCode, String streamID) {
        recordLog(MY_SELF + ": onPlayStop(" + streamID + ") --stateCode:" + stateCode);

        // 释放View
        releaseLiveView(streamID);

        mLiveCount--;
        setPublishEnabled();

        // 当一条流play失败后重新play一次
        if (stateCode == 2 && !TextUtils.isEmpty(streamID)) {
            if (!mMapReplayStreamID.get(streamID)) {
                mMapReplayStreamID.put(streamID, true);
                startPlay(streamID);
            }
        }

        mRlytControlHeader.bringToFront();
    }

    /**
     * 拉流质量更新.
     */
    protected void handlePlayQualityUpdate(String streamID, int quality, double videoFPS, double videoBitrate) {
        ViewLive viewLive = getViewLiveByStreamID(streamID);
        if (viewLive != null) {
            viewLive.setLiveQuality(quality, videoFPS, videoBitrate);
        }
    }

    /**
     * 拉流分辨率更新.
     */
    protected void handleVideoSizeChanged(String streamID, int width, int height) {
        hidePlayBackground();

        if (width > height) {
            ViewLive viewLivePlay = getViewLiveByStreamID(streamID);
            if (viewLivePlay != null) {
                if (viewLivePlay.getWidth() < viewLivePlay.getHeight()) {
                    viewLivePlay.setZegoVideoViewMode(true, ZegoVideoViewMode.ScaleAspectFit);
                    mZegoLiveRoom.setViewMode(ZegoVideoViewMode.ScaleAspectFit, streamID);
                } else {
                    viewLivePlay.setZegoVideoViewMode(true, ZegoVideoViewMode.ScaleAspectFill);
                    mZegoLiveRoom.setViewMode(ZegoVideoViewMode.ScaleAspectFill, streamID);
                }
            }
        }

        mRlytControlHeader.bringToFront();

    }

    /**
     * 房间内用户创建流.
     */
    protected void handleStreamAdded(final ZegoStreamInfo[] listStream, final String roomID) {
        if (listStream != null && listStream.length > 0) {
            for (int i = 0; i < listStream.length; i++) {
                recordLog(listStream[i].userName + ": added stream(" + listStream[i].streamID + ")");
                startPlay(listStream[i].streamID);
            }
        }
    }

    /**
     *  房间内用户删除流.
     */
    protected void handleStreamDeleted(final ZegoStreamInfo[] listStream, final String roomID) {
        if (listStream != null && listStream.length > 0) {
            for (int i = 0; i < listStream.length; i++) {
                recordLog(listStream[i].userName + ": deleted stream(" + listStream[i].streamID + ")");
                stopPlay(listStream[i].streamID);
            }
        }
    }

    /**
     * 主播登录房间.
     */
    protected void handleAnchorLoginRoom(int errorCode, ZegoStreamInfo[] zegoStreamInfos) {
        // 登录房间回调
        if(errorCode == 0){
            mPublishTitle = PreferenceUtil.getInstance().getUserName() + " is coming";
            mPublishStreamID = ZegoRoomUtil.getPublishStreamID();
            startPublish();

            // 打印log
            recordLog(MY_SELF + ": onLoginRoom success(" + mRoomID + "), streamCounts:" + zegoStreamInfos.length);
        }else {
            // 打印log
            recordLog(MY_SELF + ": onLoginRoom fail(" + mRoomID + "), errorCode:" + errorCode);
        }
    }

    /**
     * 观众登录房间
     */
    protected void handleAudienceLoginRoom(int errorCode, ZegoStreamInfo[] zegoStreamInfos) {
        // 登录房间回调
        if (errorCode == 0) {
            if (zegoStreamInfos != null && zegoStreamInfos.length > 0) {
                for (int i = 0; i < zegoStreamInfos.length; i++) {
                    startPlay(zegoStreamInfos[i].streamID);
                }
            }
            // 打印log
            recordLog(MY_SELF + ": onLoginRoom success(" + mRoomID + "), streamCounts:" + zegoStreamInfos.length);
        } else {
            // 打印log
            recordLog(MY_SELF + ": onLoginRoom fail(" + mRoomID + ") errorCode:" + errorCode);
        }
    }

    /**
     * 请求连麦.
     */
    protected  void requestJoinLive(){
        mZegoLiveRoom.requestJoinLive(new IZegoResponseCallback() {
            @Override
            public void onResponse(int result, String fromUserID, String fromUserName) {
                if (result == 0) {
                    // 连麦请求被通过
                    recordLog(getString(R.string.request_of_broadcast_has_been_allowed, MY_SELF));
                    mPublishTitle = PreferenceUtil.getInstance().getUserName() + " is coming";
                    mPublishStreamID = ZegoRoomUtil.getPublishStreamID();
                    // 推流前设置app朝向
                    setAppOrientation();
                    startPublish();
                } else {
                    // 连麦请求被拒绝
                    recordLog(getString(R.string.request_of_broadcast_has_been_denied, MY_SELF));
                    AlertDialog dialogNotify = new AlertDialog.Builder(BaseExternalRenderActivity.this).setTitle(getString(R.string.hint))
                            .setMessage(getString(R.string.your_request_has_been_denied)).setPositiveButton(getString(R.string.got_it),
                                    new DialogInterface.OnClickListener() {
                                        @Override
                                        public void onClick(DialogInterface dialog, int which) {
                                            dialog.dismiss();
                                        }
                                    }).create();
                    dialogNotify.show();
                }
            }
        });
    }

    /**
     * 响应连麦请求.
     */
    protected void handleJoinLiveRequest(final int seq, String fromUserID, String fromUserName, String roomID) {
        // 有人请求连麦
        recordLog(getString(R.string.someone_is_requesting_to_broadcast, fromUserName));
        mDialogHandleRequestPublish = new AlertDialog.Builder(BaseExternalRenderActivity.this).setTitle(getString(R.string.hint))
                .setMessage(getString(R.string.someone_is_requesting_to_broadcast_allow, fromUserName))
                .setPositiveButton(getString(R.string.Allow), new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // 同意连麦请求
                        mZegoLiveRoom.respondJoinLiveReq(seq, 0);
                        dialog.dismiss();
                    }
                }).setNegativeButton(getString(R.string.Deny), new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        // 拒绝连麦请求
                        mZegoLiveRoom.respondJoinLiveReq(seq, -1);
                        dialog.dismiss();
                    }
                }).create();

        mDialogHandleRequestPublish.show();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        // 注销电话监听
        TelephonyManager tm = (TelephonyManager) getSystemService(Service.TELEPHONY_SERVICE);
        tm.listen(mPhoneStateListener, PhoneStateListener.LISTEN_NONE);
        mPhoneStateListener = null;

        // 清空回调, 避免内存泄漏
        mZegoLiveRoom.setZegoLivePublisherCallback(null);
        mZegoLiveRoom.setZegoLivePlayerCallback(null);
        mZegoLiveRoom.setZegoRoomCallback(null);

        // 退出房间
        mZegoLiveRoom.logoutRoom();
    }


    /**
     * 设置推流朝向.
     */
    protected void setAppOrientation() {
        // 设置app朝向
        int currentOrientation = getWindowManager().getDefaultDisplay().getRotation();
        mZegoLiveRoom.setAppOrientation(currentOrientation);

        // 设置推流配置
        ZegoAvConfig currentConfig = ZegoApiManager.getInstance().getZegoAvConfig();
        int videoWidth = currentConfig.getVideoEncodeResolutionWidth();
        int videoHeight = currentConfig.getVideoEncodeResolutionHeight();
        if (((currentOrientation == Surface.ROTATION_0 || currentOrientation == Surface.ROTATION_180) && videoWidth > videoHeight) ||
                ((currentOrientation == Surface.ROTATION_90 || currentOrientation == Surface.ROTATION_270) && videoHeight > videoWidth)) {
            currentConfig.setVideoEncodeResolution(videoHeight, videoWidth);
            currentConfig.setVideoCaptureResolution(videoHeight, videoWidth);
        }
        ZegoApiManager.getInstance().setZegoConfig(currentConfig);
    }

    /**
     *  处理页面朝向变化, 目前只针对拉流.
     */
    protected void handleConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        int currentOrientation = getWindowManager().getDefaultDisplay().getRotation();
        for (ViewLive viewLive : mListViewLive) {
            if (viewLive.isPlayView()) {
                if (viewLive.isNeedToSwitchFullScreen() && viewLive.getZegoVideoViewMode() == ZegoVideoViewMode.ScaleAspectFill) {
                    if (currentOrientation == Surface.ROTATION_90 || currentOrientation == Surface.ROTATION_270) {
                        mZegoLiveRoom.setViewRotation(Surface.ROTATION_0, viewLive.getStreamID());
                    } else {
                        mZegoLiveRoom.setViewRotation(Surface.ROTATION_0, viewLive.getStreamID());
                    }
                }else {
                    mZegoLiveRoom.setViewRotation(currentOrientation, viewLive.getStreamID());
                }
            }
        }

    }

    /**
     *  归一化屏幕获取的坐标点(自定义对焦要用到)
     */
    protected List<Float> focusPointNormalize(float fx, float fy) {
        List<Float> normalizePoint = new ArrayList<>();

        if(mListViewLive.size() > 0) {
            ViewLive mLiveView = mListViewLive.get(0);

            float width = mLiveView.getWidth();
            float height = mLiveView.getHeight();
            float cx = fx / width;
            float cy = fy / height;

            normalizePoint.add(cx);
            normalizePoint.add(cy);
        }
        return normalizePoint;
    }
}
