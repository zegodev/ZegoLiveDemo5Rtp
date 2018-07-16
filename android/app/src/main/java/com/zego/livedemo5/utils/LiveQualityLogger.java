package com.zego.livedemo5.utils;

import android.os.Environment;
import android.util.Log;

import com.zego.livedemo5.ZegoApplication;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 只用于记录流的质量数据，如帧率、码率等，应用每次启动时清空上次数据
 * Created by realuei on 2017/3/24.
 */

public final class LiveQualityLogger {
    private static Writer sWriter;

    private static SimpleDateFormat sDateFormat = new SimpleDateFormat("[yy-MM-dd hh:mm:ss.SSS]: ");


    public final synchronized static boolean openAndReset() {
        if (sWriter == null && ZegoApplication.sApplicationContext != null) {
//            File externalPath = Environment.getExternalStorageDirectory();
            File externalPath = ZegoApplication.sApplicationContext.getExternalCacheDir();
            File targetFile = new File(externalPath, "zego_livedemo_live_quality.log");
            try {
                sWriter = new BufferedWriter(new FileWriter(targetFile), 2048);
            } catch (IOException e) {
                Log.w(ZegoApplication.TAG, e);
                return false;
            }
        }
        return true;
    }

    public final synchronized static boolean open() {
        if (sWriter == null && ZegoApplication.sApplicationContext != null) {
//            File externalPath = Environment.getExternalStorageDirectory();
            File externalPath = ZegoApplication.sApplicationContext.getExternalCacheDir();
            File targetFile = new File(externalPath, "zego_livedemo_live_quality.log");
            try {
                sWriter = new BufferedWriter(new FileWriter(targetFile, true), 2048);
            } catch (IOException e) {
                Log.w(ZegoApplication.TAG, e);
                return false;
            }
        }
        return true;
    }


    public final synchronized static boolean write(String text) {
        if (sWriter == null) return false;

        try {
            sWriter.write(sDateFormat.format(new Date()));
            sWriter.write(text);
            sWriter.write("\r\n");
            sWriter.flush();
        } catch (IOException e) {
            return false;
        }
        return true;
    }

    public final synchronized static boolean write(String template, Object... args) {
        if (sWriter == null) return false;

        String text = String.format(template, args);
        try {
            sWriter.write(sDateFormat.format(new Date()));
            sWriter.write(text);
            sWriter.write("\r\n");
            sWriter.flush();
        } catch (IOException e) {
            return false;
        }
        return true;
    }

    public final synchronized static boolean close() {
        if (sWriter != null) {
            try {
                sWriter.close();
                sWriter = null;
            } catch (IOException e) {
                return false;
            }
        }
        return true;
    }

}
