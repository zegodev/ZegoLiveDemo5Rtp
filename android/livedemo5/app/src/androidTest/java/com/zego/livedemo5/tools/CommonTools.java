package com.zego.livedemo5.tools;

import android.text.TextUtils;

/**
 * Created by realuei on 2017/3/15.
 */

public final class CommonTools {
    private static String LOG_PREFIX = "ESPRESSO_TEST_LOG_";

    static public void sleep(long milliSeconds) {
        try {
            Thread.sleep(milliSeconds);
        } catch (InterruptedException e) {
        }
    }

    static public void printLog(String message) {
        if (TextUtils.isEmpty(message)) {
            System.out.println();
        } else {
            System.out.print(LOG_PREFIX);
            System.out.println(message);
        }
    }

    static public void printLog(String fmt, Object... args) {
        String message = String.format(fmt, args);
        System.out.print(LOG_PREFIX);
        System.out.println(message);
    }
}
