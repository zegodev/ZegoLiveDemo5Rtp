package com.zego.livedemo5.utils;

import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Base64;
import android.util.Log;

import com.zego.livedemo5.ZegoAppHelper;
import com.zego.livedemo5.ZegoApplication;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import javax.crypto.spec.DESedeKeySpec;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des: Preference管理工具类.
 */
public class PreferenceUtil {

    /**
     * 单例.
     */
    public static PreferenceUtil sInstance;


    public static final String SHARE_PREFERENCE_NAME = "ZEGO_LIVE_DEMO5";

    public static final String PREFERENCE_KEY_USER_ID = "PREFERENCE_KEY_USER_ID";

    public static final String PREFERENCE_KEY_USER_NAME = "PREFERENCE_KEY_USER_NAME";

    private static final String Pref_key_App_Id = "zego_app_id";
    private static final String Pref_key_App_Key = "zego_app_key";
    private static final String ZEGO_APP_WEBRTC = "zego_app_webrtc";

    public static final String KEY_APP_FLAVOR = "zego_app_flavor_index";

    public static final String ZEGO_APP_CUSTOM = "zego_app_custom";
    public static final String ZEGO_APP_KEY_CUSTOM = "zego_app_key_custom";
    public static final String ZEGO_LIVE_LIVE_QUALITY = "ZEGO_LIVE_LIVE_QUALITY";
    public static final String VIDEO_RESOLUTIONS = "VIDEO_RESOLUTIONS";
    public static final String VIDEO_FPS = "VIDEO_FPS";
    public static final String VIDEO_BITRATE = "VIDEO_BITRATE";
    public static final String VIDEO_FILTER = "VIDEO_FILTER";
    public static final String VIDEO_CAPTURE = "VIDEO_CAPTURE";
    public static final String EXTERNAL_RENDER = "EXTERNAL_RENDER";
    public static final String PREVIEW_MIRROR = "PREVIEW_MIRROR";
    public static final String CAPTURE_MIRROR = "CAPTURE_MIRROR";
    public static final String USE_TEST_EVN = "USE_TEST_EVN";
    public static final String ENABLE_RATE_CONTROL = "ENABLE_RATE_CONTROL";
    public static final String REQUIRE_HARDWARE_ENCODER = "REQUIRE_HARDWARE_ENCODER";
    public static final String REQUIRE_HARDWARE_DECODER = "REQUIRE_HARDWARE_DECODER";

    static private String ZEGO_SDK_APP_BUSINESS_TYPE = "_zego_app_business_type";

    static private String ZEGO_APP_INTERNATIONAL = "zego_app_international";

    private SharedPreferences mSharedPreferences;

    private PreferenceUtil() {
        mSharedPreferences = ZegoApplication.sApplicationContext.getSharedPreferences(SHARE_PREFERENCE_NAME, AppCompatActivity.MODE_PRIVATE);
    }

    public static PreferenceUtil getInstance() {
        if (sInstance == null) {
            synchronized (PreferenceUtil.class) {
                if (sInstance == null) {
                    sInstance = new PreferenceUtil();
                }
            }
        }
        return sInstance;
    }

    public void setStringValue(String key, String value) {
        SharedPreferences.Editor editor = mSharedPreferences.edit();
        editor.putString(key, value);
        editor.commit();
    }

    public String getStringValue(String key, String defaultValue) {
        return mSharedPreferences.getString(key, defaultValue);
    }

    public void setBooleanValue(String key, boolean value) {
        SharedPreferences.Editor editor = mSharedPreferences.edit();
        editor.putBoolean(key, value);
        editor.commit();
    }


    public boolean getBooleanValue(String key, boolean defaultValue) {
        return mSharedPreferences.getBoolean(key, defaultValue);
    }

    public void setIntValue(String key, int value) {
        SharedPreferences.Editor editor = mSharedPreferences.edit();
        editor.putInt(key, value);
        editor.commit();
    }

    public int getIntValue(String key, int defaultValue) {
        return mSharedPreferences.getInt(key, defaultValue);
    }

    public void setLongValue(String key, long value) {
        SharedPreferences.Editor editor = mSharedPreferences.edit();
        editor.putLong(key, value);
        editor.commit();
    }

    public long getLongValue(String key, long defaultValue) {
        return mSharedPreferences.getLong(key, defaultValue);
    }

    public void setUserID(String userID) {
        setStringValue(PREFERENCE_KEY_USER_ID, userID);
    }

    public String getUserID() {
        return getStringValue(PREFERENCE_KEY_USER_ID, null);
    }

    public void setUserName(String userName) {
        setStringValue(PREFERENCE_KEY_USER_NAME, userName);
    }

    public String getUserName() {
        return getStringValue(PREFERENCE_KEY_USER_NAME, null);
    }

    public void setAppId(long appId) {
        setLongValue(Pref_key_App_Id, appId);
    }

    public long getAppId() {
        return getLongValue(Pref_key_App_Id, -1);
    }

    public int getCurrentAppFlavor() {
        return getIntValue(KEY_APP_FLAVOR, -1);
    }

    public void setAppFlavor(int appFlavorIndex) {
        setIntValue(KEY_APP_FLAVOR, appFlavorIndex);
    }

    public void setAppKey(byte[] signKey) {
        String strSignKey = ZegoAppHelper.convertSignKey2String(signKey);
        setStringValue(Pref_key_App_Key, strSignKey);
    }

    public byte[] getAppKey() {
        String strSignKey = getStringValue(Pref_key_App_Key, null);
        if (TextUtils.isEmpty(strSignKey)) {
            return null;
        }
        try {
            return ZegoAppHelper.parseSignKeyFromString(strSignKey);
        } catch (NumberFormatException e) {
        }
        return null;
    }

    public String getAppKeyToStr() {
        String strSignKey = getStringValue(Pref_key_App_Key, null);

        return strSignKey;
    }

    public String getAppKeyCustomToStr() {
        String strSignKey = getStringValue(ZEGO_APP_KEY_CUSTOM, null);

        return strSignKey;
    }

    public Object getObjectFromString(String key) {
        Object value = null;
        try {
            byte[] bytes = Base64.decode(PreferenceUtil.getInstance().getStringValue(key, ""), Base64.DEFAULT);
            ByteArrayInputStream bais = new ByteArrayInputStream(bytes);
            ObjectInputStream oisArray = new ObjectInputStream(bais);
            value = oisArray.readObject();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return value;
    }

    public void setObjectToString(String key, Object value) {

        try {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ObjectOutputStream oos;
            oos = new ObjectOutputStream(baos);
            oos.writeObject(value);
            String data = new String(Base64.encodeToString(baos.toByteArray(), Base64.DEFAULT));
            PreferenceUtil.getInstance().setStringValue(key, data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void registerOnChangeListener(OnChangeListener listener) {
        mSharedPreferences.registerOnSharedPreferenceChangeListener(listener);
    }

    public void unregisterOnChangeListener(OnChangeListener listener) {
        mSharedPreferences.unregisterOnSharedPreferenceChangeListener(listener);
    }


    public void setLiveQuality(int liveQuality) {
        setIntValue(ZEGO_LIVE_LIVE_QUALITY, liveQuality);
    }

    public void setVideoResolutions(int videoResolutions) {
        setIntValue(VIDEO_RESOLUTIONS, videoResolutions);
    }

    public void setVideoFps(int videoFps) {
        setIntValue(VIDEO_FPS, videoFps);
    }

    public void setVideoBitrate(int videoBitrate) {
        setIntValue(VIDEO_BITRATE, videoBitrate);
    }

    public void setVideoFilter(boolean videoFilter) {
        setBooleanValue(VIDEO_FILTER, videoFilter);
    }

    public void setVideoCapture(boolean videoCapture) {
        setBooleanValue(VIDEO_CAPTURE, videoCapture);
    }

    public void setExternalRender(boolean externalRender) {
        setBooleanValue(EXTERNAL_RENDER, externalRender);
    }

    public void setPreviewMirror(boolean previewMirror) {
        setBooleanValue(PREVIEW_MIRROR, previewMirror);
    }

    public void setCaptureMirror(boolean captureMirror) {
        setBooleanValue(CAPTURE_MIRROR, captureMirror);
    }


    public void setUseTestEvn(boolean useTestEvn) {
        setBooleanValue(USE_TEST_EVN, useTestEvn);
    }

    public void setEnableRateControl(boolean enableRateControl) {
        Log.e("zego", "REQUIRE_HARDWARE_ENCODER" + "=" + enableRateControl);
        setBooleanValue(ENABLE_RATE_CONTROL, enableRateControl);
    }

    public void setRequireHardwareEncoder(boolean requireHardwareEncoder) {
        setBooleanValue(REQUIRE_HARDWARE_ENCODER, requireHardwareEncoder);

    }

    public void setRequireHardwareDecoder(boolean requireHardwareDecoder) {
        setBooleanValue(REQUIRE_HARDWARE_DECODER, requireHardwareDecoder);
    }

    public boolean getTestEnv(boolean defaultValue) {
        return getBooleanValue(USE_TEST_EVN, defaultValue);
    }

    public boolean getVideoCapture(boolean defaultValue) {
        return getBooleanValue(VIDEO_CAPTURE, defaultValue);
    }

    public boolean getUseExternalRender(boolean defaultValue) {
        return getBooleanValue(EXTERNAL_RENDER, defaultValue);
    }

    public boolean getVideoFilter(boolean defaultValue) {

        return getBooleanValue(VIDEO_FILTER, defaultValue);
    }

    public boolean getHardwareEncode(boolean defaultValue) {

        return getBooleanValue(REQUIRE_HARDWARE_ENCODER, defaultValue);
    }

    public boolean getHardwareDecode(boolean defaultValue) {
        return getBooleanValue(REQUIRE_HARDWARE_DECODER, defaultValue);
    }

    public boolean getEnableRateControl(boolean defaultValue) {
        return getBooleanValue(ENABLE_RATE_CONTROL, defaultValue);
    }

    public boolean getPreviewMirror(boolean defaultValue) {
        return getBooleanValue(PREVIEW_MIRROR, defaultValue);
    }

    public boolean getCaptureMirror(boolean defaultValue) {
        return getBooleanValue(CAPTURE_MIRROR, defaultValue);
    }

    public int getLiveQuality(int defaultValue) {

        return getIntValue("ZEGO_LIVE_LIVE_QUALITY", defaultValue);
    }

    public int getVideoResolutions(int defaultValue) {

        return getIntValue(VIDEO_RESOLUTIONS, defaultValue);
    }

    public int getVideoFps(int defaultValue) {

        return getIntValue(VIDEO_FPS, defaultValue);
    }

    public int getVideoBitrate(int defaultValue) {
        return getIntValue(VIDEO_BITRATE, defaultValue);
    }


    public void setBusinessType(int businessType) {
        setIntValue(ZEGO_SDK_APP_BUSINESS_TYPE, businessType);
    }

    public void setInternational(boolean international) {
        setBooleanValue(ZEGO_APP_INTERNATIONAL, international);
    }

    public int getBusinessType() {
        return getIntValue(ZEGO_SDK_APP_BUSINESS_TYPE, 0);
    }


    public interface OnChangeListener extends SharedPreferences.OnSharedPreferenceChangeListener {

    }
}
