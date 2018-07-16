package com.zego.livedemo5.tools;

import android.os.Build;
import android.support.test.InstrumentationRegistry;
import android.support.test.uiautomator.UiDevice;
import android.support.test.uiautomator.UiObject;
import android.support.test.uiautomator.UiObjectNotFoundException;
import android.support.test.uiautomator.UiSelector;

import static com.zego.livedemo5.tools.CommonTools.printLog;
import static com.zego.livedemo5.tools.CommonTools.sleep;

/**
 * Created by realuei on 2017/3/21.
 */

@SuppressWarnings("unused")
public final class PermissionTool {

    /**
     * 检查并处理是否弹出权限申请对话框，如果存在，则模拟点击允许（需要分机型处理，不同机型上对话框的实现控件不一样）
     */
    public static void allowPermissionIfNeed() {
        if (isMeizu() || isMIUI()) {
            allowPermissionMeiZu();
        } else {
            allowPermissionAndroid();
        }
    }

    private static boolean brandContains(String text) {
        return Build.BRAND.toLowerCase().contains(text)
                || Build.MANUFACTURER.toLowerCase().contains(text)
                || Build.FINGERPRINT.toLowerCase().contains(text);
    }

    private static boolean isMeizu() {
        return brandContains("meizu");
    }

    private static boolean isMIUI() {
        return brandContains("xiaomi");
    }

    private static void allowPermissionAndroid() {
        clickAllowButtonInPermissionDialog("android.widget.Button", "com.android.packageinstaller:id/permission_allow_button");
    }

    private static void allowPermissionMeiZu() {
        clickAllowButtonInPermissionDialog("android.widget.Button", "android:id/button1");
    }

    public static void clickToGetPermission(int waitTime){
        sleep(1000);
        UiDevice uiDevice=UiDevice.getInstance(InstrumentationRegistry.getInstrumentation());
        UiObject button=uiDevice.findObject(new UiSelector().className("android.widget.Button").text("允许"));

        if(button.waitForExists(waitTime*1000)){
            try {
                button.click();
                clickToGetPermission(waitTime);
            } catch (UiObjectNotFoundException e) {
                e.printStackTrace();
            }
        }
    }

    private static void clickAllowButtonInPermissionDialog(String btnClassName, String btnResId) {
        printLog("get UiDevice instance");
        android.support.test.uiautomator.UiDevice device = UiDevice.getInstance(InstrumentationRegistry.getInstrumentation());
        printLog("UiDevice instance: %s", device);
        UiObject allowPermission = device.findObject(new UiSelector().className(btnClassName).resourceId(btnResId));
        printLog("find allow permission dialog button: %s, exists: %s", allowPermission, allowPermission.exists());
        if (allowPermission.waitForExists(1000)) {
            try {
                allowPermission.click();
                clickAllowButtonInPermissionDialog(btnClassName, btnResId);
            } catch (UiObjectNotFoundException e) {
                printLog("There is no permissions dialog to interact with %s", e);
            }
        } else {
            printLog("allow permission dialog not exists");
        }
    }

    /**
     * 动态添加权限，只对不需要在应用中申请的权限有效，如：android.permission.INTERNET；如果是必须应用中动态申请（即用户同意）的权限，此方法无效，如：android.permission.CAMERA 等
     * @param permission 需要动态申请的权限
     */
    public static void grantPhonePermission(String permission) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            String grantCommand = String.format("pm grant %s %s", InstrumentationRegistry.getTargetContext().getPackageName(), permission);
            InstrumentationRegistry.getInstrumentation().getUiAutomation().executeShellCommand(grantCommand);
        }
    }

    /**
     * 释放权限
     * @param permission 需要动态释放的权限
     */
    public static void revokePhonePermission(String permission) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            String revokeCommand = String.format("pm revoke %s %s", InstrumentationRegistry.getTargetContext().getPackageName(), permission);
            InstrumentationRegistry.getInstrumentation().getUiAutomation().executeShellCommand(revokeCommand);
        }
    }
}
