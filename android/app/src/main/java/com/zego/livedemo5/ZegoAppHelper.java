package com.zego.livedemo5;

import android.content.Context;
import android.content.res.Resources;
import android.os.Handler;
import android.os.HandlerThread;

/**
 * Created by realuei on 2017/6/29.
 */

public class ZegoAppHelper {

    /**
     * 请开发者联系 ZEGO support 获取各自业务的 AppID 与 signKey
     * Demo 默认使用 UDP 模式，请填充该模式下的 AppID 与 signKey,其他模式不需要可不用填
     * AppID 填写样式示例：1234567890l
     * signKey 填写样式示例：{(byte)0x00,(byte)0x01,(byte)0x02,(byte)0x03}
     **/

    static final public long RTMP_APP_ID = 1L;

    static final public long UDP_APP_ID = 1739272706L;

    static final public long INTERNATIONAL_APP_ID = 3322882036L;

    static final private byte[] RTMP_SIGN_KEY = new byte[]{(byte) 0x91, (byte) 0x93, (byte) 0xcc, (byte) 0x66, (byte) 0x2a, (byte) 0x1c, (byte) 0x0e, (byte) 0xc1,
            (byte) 0x35, (byte) 0xec, (byte) 0x71, (byte) 0xfb, (byte) 0x07, (byte) 0x19, (byte) 0x4b, (byte) 0x38,
            (byte) 0x41, (byte) 0xd4, (byte) 0xad, (byte) 0x83, (byte) 0x78, (byte) 0xf2, (byte) 0x59, (byte) 0x90,
            (byte) 0xe0, (byte) 0xa4, (byte) 0x0c, (byte) 0x7f, (byte) 0xf4, (byte) 0x28, (byte) 0x41, (byte) 0xf7};

    static final private byte[] UDP_SIGN_KEY = new byte[]{(byte) 0x1e, (byte) 0xc3, (byte) 0xf8, (byte) 0x5c, (byte) 0xb2, (byte) 0xf2, (byte) 0x13, (byte) 0x70,
            (byte) 0x26, (byte) 0x4e, (byte) 0xb3, (byte) 0x71, (byte) 0xc8, (byte) 0xc6, (byte) 0x5c, (byte) 0xa3,
            (byte) 0x7f, (byte) 0xa3, (byte) 0x3b, (byte) 0x9d, (byte) 0xef, (byte) 0xef, (byte) 0x2a, (byte) 0x85,
            (byte) 0xe0, (byte) 0xc8, (byte) 0x99, (byte) 0xae, (byte) 0x82, (byte) 0xc0, (byte) 0xf6, (byte) 0xf8};

    static final private byte[] INTERNATIONAL_SIGN_KEY = new byte[]{(byte) 0x5d, (byte) 0xe6, (byte) 0x83, (byte) 0xac, (byte) 0xa4, (byte) 0xe5, (byte) 0xad, (byte) 0x43,
            (byte) 0xe5, (byte) 0xea, (byte) 0xe3, (byte) 0x70, (byte) 0x6b, (byte) 0xe0, (byte) 0x77, (byte) 0xa4,
            (byte) 0x18, (byte) 0x79, (byte) 0x38, (byte) 0x31, (byte) 0x2e, (byte) 0xcc, (byte) 0x17, (byte) 0x19,
            (byte) 0x32, (byte) 0xd2, (byte) 0xfe, (byte) 0x22, (byte) 0x5b, (byte) 0x6b, (byte) 0x2b, (byte) 0x2f};

    private static ZegoAppHelper sInstance = new ZegoAppHelper();

    private HandlerThread _backgroundThread = new HandlerThread("zego_background");
    private Handler backgroundHandler;

    private ZegoAppHelper() {
        _backgroundThread.start();
        backgroundHandler = new Handler(_backgroundThread.getLooper());
    }

    /**
     * 在后台执行一个任务，相比普通 Thread，可以对所有待执行的任务排序
     *
     * @param runnable
     */
    static public void postTask(Runnable runnable) {
        sInstance.backgroundHandler.post(runnable);
    }

    /**
     * 移除所有后台任务
     */
    static public void removeTask(Runnable runnable) {
        sInstance.backgroundHandler.removeCallbacks(runnable);
    }

    static public boolean isInternationalProduct(long appId) {
        return appId == INTERNATIONAL_APP_ID;
    }

    static public boolean isUdpProduct(long appId) {
        return appId == UDP_APP_ID;
    }

    static public boolean isRtmpProduct(long appId) {
        return appId == RTMP_APP_ID;
    }

    static public boolean isAppIdVersion(long appId) {
        if (isRtmpProduct(appId)) {
            return true;
        } else if (isUdpProduct(appId)) {
            return true;
        } else if (isInternationalProduct(appId)) {
            return true;
        }
        return false;
    }


    static public byte[] requestSignKey(long appId) {
        if (isRtmpProduct(appId)) {
            return RTMP_SIGN_KEY;
        } else if (isUdpProduct(appId)) {
            return UDP_SIGN_KEY;
        } else if (isInternationalProduct(appId)) {
            return INTERNATIONAL_SIGN_KEY;
        }
        return null;
    }

    static public String getAppTitle(long appId, Context context) {
        String appTitle;
        Resources resources = context.getResources();
        if (appId == 0) {   // UDP
            appTitle = resources.getString(R.string.app_title, "UDP");
        } else if (appId == 1) {   // International
            appTitle = resources.getString(R.string.app_title, "Int'l");
        } else {    // Custom
            appTitle = resources.getString(R.string.app_title, "Custom");
        }
        return appTitle;
    }

    static public String convertSignKey2String(byte[] signKey) {
        StringBuilder buffer = new StringBuilder();
        for (int b : signKey) {
            buffer.append("0x").append(Integer.toHexString((b & 0x000000FF) | 0xFFFFFF00).substring(6)).append(",");
        }
        buffer.setLength(buffer.length() - 1);
        return buffer.toString();
    }

    static public byte[] parseSignKeyFromString(String strSignKey) throws NumberFormatException {
        String[] keys = strSignKey.split(",");
        if (keys.length != 32) {
            throw new NumberFormatException("App Sign Key Illegal");
        }
        byte[] byteSignKey = new byte[32];
        for (int i = 0; i < 32; i++) {
            int data = Integer.valueOf(keys[i].trim().replace("0x", ""), 16);
            byteSignKey[i] = (byte) data;
        }
        return byteSignKey;
    }
}
