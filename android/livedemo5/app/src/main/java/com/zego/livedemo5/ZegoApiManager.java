package com.zego.livedemo5;


import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;

import com.zego.livedemo5.constants.Constants;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.livedemo5.utils.SystemUtil;
import com.zego.livedemo5.videocapture.VideoCaptureFactoryDemo;
import com.zego.livedemo5.videofilter.VideoFilterFactoryDemo;
import com.zego.zegoavkit2.ZegoConstants;
import com.zego.zegoavkit2.ZegoExternalVideoCapture;
import com.zego.zegoavkit2.enums.VideoExternalRenderType;
import com.zego.zegoavkit2.videofilter.ZegoExternalVideoFilter;
import com.zego.zegoavkit2.videorender.ZegoExternalVideoRender;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.callback.IZegoInitSDKCompletionCallback;
import com.zego.zegoliveroom.constants.ZegoAvConfig;

import static com.zego.livedemo5.constants.Constants.ZEGO_ROTATION_270;

/**
 * des: zego api管理器.
 */
public class ZegoApiManager {

    private static ZegoApiManager sInstance = null;

    private ZegoLiveRoom mZegoLiveRoom = null;

    private ZegoAvConfig zegoAvConfig;

    public long getCurrentAppID() {
        return currentAppID;
    }

    public void setCurrentAppID(long currentAppID) {
        this.currentAppID = currentAppID;
    }

    // 当前initSDK的appid
    private long currentAppID;

    private final int[][] VIDEO_RESOLUTIONS = new int[][]{{320, 240}, {352, 288}, {640, 360},
            {960, 540}, {1280, 720}, {1920, 1080}};


    private byte[] mSignKey = null;

    public boolean isAlphaEnv = false;

    private ZegoApiManager() {
        mZegoLiveRoom = new ZegoLiveRoom();
    }

    public static ZegoApiManager getInstance() {
        if (sInstance == null) {
            synchronized (ZegoApiManager.class) {
                if (sInstance == null) {
                    sInstance = new ZegoApiManager();
                }
            }
        }
        return sInstance;
    }

    /**
     * 高级功能.
     */
    private void openAdvancedFunctions() {

        // 开启测试环境
        if (PreferenceUtil.getInstance().getTestEnv(false)) {
            ZegoLiveRoom.setTestEnv(true);
        }

//        // 外部渲染
//        if (PreferenceUtil.getInstance().getUseExternalRender(false)) {
//            // 开启外部渲染
//            ZegoExternalVideoRender.enableExternalRender(true, VideoExternalRenderType.DECODE_RGB_SERIES);
//        }

        // 外部采集
        if (PreferenceUtil.getInstance().getVideoCapture(false)) {
            // 外部采集
            VideoCaptureFactoryDemo factoryDemo = new VideoCaptureFactoryDemo();
            factoryDemo.setContext(ZegoApplication.sApplicationContext);
            ZegoExternalVideoCapture.setVideoCaptureFactory(factoryDemo, com.zego.zegoavkit2.ZegoConstants.PublishChannelIndex.MAIN);
        }

        // 外部滤镜
        if (PreferenceUtil.getInstance().getVideoFilter(false)) {
            // 外部滤镜
            VideoFilterFactoryDemo videoFilterFactoryDemo = new VideoFilterFactoryDemo();
            ZegoExternalVideoFilter.setVideoFilterFactory(videoFilterFactoryDemo, com.zego.zegoavkit2.ZegoConstants.PublishChannelIndex.MAIN);
        }
    }


    private void initUserInfo() {
        // 初始化用户信息
        String userID = PreferenceUtil.getInstance().getUserID();
        String userName = PreferenceUtil.getInstance().getUserName();

        if (TextUtils.isEmpty(userID) || TextUtils.isEmpty(userName)) {
            long ms = System.currentTimeMillis();
            userID = ms + "";
            userName = "Android_" + SystemUtil.getOsInfo() + "-" + ms;

            // 保存用户信息
            PreferenceUtil.getInstance().setUserID(userID);
            PreferenceUtil.getInstance().setUserName(userName);
        }
        // 必须设置用户信息
        ZegoLiveRoom.setUser(userID, userName);

    }

    public void setAlphaEnv(boolean env){
        isAlphaEnv = env;
        releaseSDK();
        ZegoApplication.zgAppSupportApi.api().setUseAlphaEnv(env);
        initSDK();

    }


    private IZegoInitSDKCompletionCallback iZegoInitSDKCompletionCallback;

    private void init(long appID, byte[] signKey, boolean isConfig) {

        initUserInfo();

        // 开发者根据需求定制
        openAdvancedFunctions();

        // 设置视频通话类型
        ZegoLiveRoom.setBusinessType(PreferenceUtil.getInstance().getBusinessType());

        // 当前appId
        currentAppID = appID;

        // 初始化sdk
        boolean ret = mZegoLiveRoom.initSDK(appID, signKey, iZegoInitSDKCompletionCallback);

        if (!ret) {
            // sdk初始化失败
            Toast.makeText(ZegoApplication.sApplicationContext, "Zego SDK初始化失败!", Toast.LENGTH_LONG).show();
        } else if (isConfig) {
            int liveQualityLevel = PreferenceUtil.getInstance().getLiveQuality(3);
            switch (liveQualityLevel) {
                case 0:
                    zegoAvConfig = new ZegoAvConfig(ZegoAvConfig.Level.VeryLow);
                    break;
                case 1:
                    zegoAvConfig = new ZegoAvConfig(ZegoAvConfig.Level.Low);
                    break;
                case 2:
                    zegoAvConfig = new ZegoAvConfig(ZegoAvConfig.Level.Generic);
                    break;
                case 3:
                    zegoAvConfig = new ZegoAvConfig(ZegoAvConfig.Level.High);
                    break;
                case 4:
                    zegoAvConfig = new ZegoAvConfig(ZegoAvConfig.Level.VeryHigh);
                    break;
                case 5:
                    zegoAvConfig = new ZegoAvConfig(ZegoAvConfig.Level.SuperHigh);
                    break;
                case 6:
                    // 自定义设置
                    zegoAvConfig = initZegoAvConfig(Constants.ZEGO_ROTATION_0);
                    break;
            }

            if (isConfig) {
                mZegoLiveRoom.setAVConfig(zegoAvConfig);
            }

            // 开发者根据需求定制
            // 硬件编码
            setUseHardwareEncode(PreferenceUtil.getInstance().getHardwareEncode(true));
            // 硬件解码
            setUseHardwareDecode(PreferenceUtil.getInstance().getHardwareDecode(true));
            // 码率控制
            setUseRateControl(PreferenceUtil.getInstance().getEnableRateControl(false));

        }


    }

    /**
     * 刷新配置
     *
     * @param orientation 竖屏还是横屏
     */
    public void refreshZegoAvConfig(int orientation) {
        zegoAvConfig = initZegoAvConfig(orientation);
        mZegoLiveRoom.setAVConfig(zegoAvConfig);
    }

    public ZegoAvConfig initZegoAvConfig(int orientation) {
        int liveQualityLevel = PreferenceUtil.getInstance().getLiveQuality(3);
        //默认竖屏
        int number = 1;
        if (orientation == ZEGO_ROTATION_270) {
            //切换横屏
            number = 0;
        }

        zegoAvConfig = ZegoApiManager.getInstance().getZegoAvConfig();

        int progress = PreferenceUtil.getInstance().getVideoResolutions(0);
        if (liveQualityLevel != 6) {
            progress = liveQualityLevel;
        }
        int width = VIDEO_RESOLUTIONS[progress][number];
        int height = VIDEO_RESOLUTIONS[progress][number == 0 ? 1 : 0];
        Log.e("initZegoAvConfig", String.format("width: %d", width));
        Log.e("initZegoAvConfig", String.format("height: %d", height));
        zegoAvConfig.setVideoEncodeResolution(width, height);
        zegoAvConfig.setVideoCaptureResolution(width, height);

        return zegoAvConfig;
    }

    /**
     * 此方法是通过 appId 模拟获取与之对应的 signKey，强烈建议 signKey 不要存储在本地，而是加密存储在云端，通过网络接口获取
     *
     * @param appId
     * @return
     */
    private byte[] requestSignKey(long appId) {
        return ZegoAppHelper.requestSignKey(appId);
    }

    /**
     * 初始化sdk.
     */
    public void initSDK() {
        initSDK(true);
    }

    public void setZegoInitSDKCompletionCallback(IZegoInitSDKCompletionCallback iZegoInitSDKCompletionCallback) {
        this.iZegoInitSDKCompletionCallback = iZegoInitSDKCompletionCallback;
    }

    /**
     * 初始化sdk.
     *
     * @param isConfig 是否加载分辨率配置
     */
    public void initSDK(boolean isConfig) {

        long appId;
        byte[] signKey;
        int currentAppFlavor = PreferenceUtil.getInstance().getCurrentAppFlavor();
        if (currentAppFlavor <= 1) {
            if (currentAppFlavor == -1 || currentAppFlavor == 0) {
                appId = ZegoAppHelper.UDP_APP_ID;
                signKey = ZegoAppHelper.requestSignKey(ZegoAppHelper.UDP_APP_ID);
            } else {
                appId = ZegoAppHelper.INTERNATIONAL_APP_ID;
                signKey = ZegoAppHelper.requestSignKey(ZegoAppHelper.INTERNATIONAL_APP_ID);
            }

        } else {
            appId = PreferenceUtil.getInstance().getAppId();
            signKey = PreferenceUtil.getInstance().getAppKey();
        }

        init(appId, signKey, isConfig);
    }

    public void reInitSDK(long appID, byte[] signKey) {
        init(appID, signKey, true);
    }

    public void releaseSDK() {
        // 清空高级设置
        ZegoLiveRoom.setTestEnv(false);

        // 先置空factory后unintSDK, 或者调换顺序，factory中的destroy方法都会被回调
        ZegoExternalVideoCapture.setVideoCaptureFactory(null, ZegoConstants.PublishChannelIndex.MAIN);
        ZegoExternalVideoFilter.setVideoFilterFactory(null, ZegoConstants.PublishChannelIndex.MAIN);
        mZegoLiveRoom.unInitSDK();

        ZegoApplication.setupSDKContext();
    }

    public ZegoLiveRoom getZegoLiveRoom() {
        return mZegoLiveRoom;
    }

    public void setZegoConfig(ZegoAvConfig config) {
        zegoAvConfig = config;
        mZegoLiveRoom.setAVConfig(config);
    }


    public ZegoAvConfig getZegoAvConfig() {
        if (zegoAvConfig == null) {
            synchronized (ZegoApiManager.class) {
                if (zegoAvConfig == null) {
                    zegoAvConfig = new ZegoAvConfig(ZegoAvConfig.Level.High);
                }
            }
        }
        return zegoAvConfig;
    }


    public void setUseTestEvn(boolean useTestEvn) {

        PreferenceUtil.getInstance().setUseTestEvn(useTestEvn);
    }

    public boolean isUseExternalRender() {
        return PreferenceUtil.getInstance().getUseExternalRender(false);
    }

    public void setUseExternalRender(boolean useExternalRender) {

        PreferenceUtil.getInstance().setExternalRender(useExternalRender);
    }

    public void setUseVideoCapture(boolean useVideoCapture) {

        PreferenceUtil.getInstance().setVideoCapture(useVideoCapture);
    }

    public void setUseVideoFilter(boolean useVideoFilter) {

        PreferenceUtil.getInstance().setVideoFilter(useVideoFilter);
    }

    public boolean isUseVideoCapture() {
        return PreferenceUtil.getInstance().getVideoCapture(false);
    }

    public boolean isUseVideoFilter() {
        return PreferenceUtil.getInstance().getVideoFilter(false);
    }

    public void setUseHardwareEncode(boolean useHardwareEncode) {
        if (useHardwareEncode) {
            // 开硬编时, 关闭码率控制
            if (PreferenceUtil.getInstance().getEnableRateControl(false)) {
                mZegoLiveRoom.enableRateControl(false);
                PreferenceUtil.getInstance().setEnableRateControl(false);
            }
        }
        ZegoLiveRoom.requireHardwareEncoder(useHardwareEncode);

        PreferenceUtil.getInstance().setRequireHardwareEncoder(useHardwareEncode);
    }

    public void setUseHardwareDecode(boolean useHardwareDecode) {
        ZegoLiveRoom.requireHardwareDecoder(useHardwareDecode);
        PreferenceUtil.getInstance().setRequireHardwareDecoder(useHardwareDecode);
    }

    public void setUseRateControl(boolean useRateControl) {
        if (useRateControl) {
            // 开码率控制时, 关硬编
            if (PreferenceUtil.getInstance().getHardwareEncode(true)) {
                ZegoLiveRoom.requireHardwareEncoder(false);
                PreferenceUtil.getInstance().setRequireHardwareEncoder(false);
            }
        }
        PreferenceUtil.getInstance().setEnableRateControl(useRateControl);
        mZegoLiveRoom.enableRateControl(useRateControl);
    }

    public long getAppID() {
        return PreferenceUtil.getInstance().getAppId();
    }

    public byte[] getSignKey() {
        return mSignKey;
    }

    public boolean isUseTestEvn() {
        return PreferenceUtil.getInstance().getTestEnv(false);
    }

}
