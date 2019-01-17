package com.zego.livedemo5.utils;

import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.util.DisplayMetrics;


import com.zego.livedemo5.R;
import com.zego.livedemo5.ZegoApplication;

import java.util.List;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class SystemUtil {
    public static String getAppVersionName(Context context) {

        String versionName = context.getString(R.string.demo_version);

        try {
            PackageManager manager = context.getPackageManager();
            PackageInfo info = manager.getPackageInfo(context.getPackageName(), 0);
            versionName = versionName + info.versionName;
        } catch (Exception e) {
            e.printStackTrace();
        }

        return versionName;
    }

    public static boolean isDebugVersion(Context context) {
        try {
            ApplicationInfo info = context.getApplicationInfo();
            return (info.flags & ApplicationInfo.FLAG_DEBUGGABLE) != 0;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static boolean isAppBackground() {

        ActivityManager activityManager = (ActivityManager) ZegoApplication.sApplicationContext
                .getSystemService(Context.ACTIVITY_SERVICE);
        List<ActivityManager.RunningAppProcessInfo> appProcesses = activityManager
                .getRunningAppProcesses();

        for (ActivityManager.RunningAppProcessInfo appProcess : appProcesses) {
            if (appProcess.processName.equals(ZegoApplication.sApplicationContext.getPackageName())) {
                if (appProcess.importance == ActivityManager.RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
                    return true;
                } else {
                    return false;
                }
            }
        }
        return false;
    }

    static public String getOsInfo() {

        // 上报系统信息
        StringBuilder oriInfo = new StringBuilder();
        oriInfo.append(Build.MODEL);

        // 替换字符串中的","
        String finalInfo = oriInfo.toString().replaceAll(",", ".");

        return finalInfo;
    }

    /**
     * 获取屏幕分辨率比例
     *
     * @param context
     * @return 返回true 为横屏比例, 返回false 为竖屏比例
     */
    static public boolean getResolutionProportion(Context context) {

        // 获取屏幕分辨率. 判断屏幕比例
        DisplayMetrics dm = context.getResources().getDisplayMetrics();
        int width = dm.widthPixels;
        int height = dm.heightPixels;
        if (width > height) {
            return true;
        }
        return false;
    }
}
