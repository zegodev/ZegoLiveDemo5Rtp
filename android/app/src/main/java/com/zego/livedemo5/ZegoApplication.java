package com.zego.livedemo5;

import android.app.Application;
import android.content.Context;
import android.os.Looper;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;
import android.widget.Toast;

import com.tencent.bugly.crashreport.CrashReport;
import com.zego.livedemo5.utils.LiveQualityLogger;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.support.AppType;
import com.zego.support.api.ZGAppSupportHelper;
import com.zego.zegoliveroom.ZegoLiveRoom;


/**
 * des: 自定义Application.
 */
public class ZegoApplication extends android.support.multidex.MultiDexApplication implements Thread.UncaughtExceptionHandler {

    public static final String TAG = ZegoApplication.class.getSimpleName();

    public static ZegoApplication sApplicationContext;

    Thread.UncaughtExceptionHandler mDefaultHandler;

    public static ZGAppSupportHelper zgAppSupportApi;

    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
        sApplicationContext = this;
    }

    @Override
    public void onCreate() {
        super.onCreate();

        setupSDKContext();

        zgAppSupportApi = ZGAppSupportHelper.create(this);
        zgAppSupportApi.api().setAutoConfigParams(AppType.LIVE_DEMO5, "");

        // bugly初始化用户id
        CrashReport.initCrashReport(getApplicationContext(), "2da9d0c1ef", false);
        CrashReport.setUserId(PreferenceUtil.getInstance().getUserID());

        LiveQualityLogger.openAndReset();
    }

    public Context getApplicationContext() {
        return sApplicationContext;
    }

    /**
     * 当UncaughtException发生时会转入该函数来处理
     */
    @Override
    public void uncaughtException(Thread thread, Throwable ex) {
        if (!handleException(ex) && mDefaultHandler != null) {
            //如果用户没有处理则让系统默认的异常处理器来处理
            mDefaultHandler.uncaughtException(thread, ex);
        } else {
            try {
                // 暂停3秒
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                Log.e(TAG, "error : ", e);
            }
            // 退出程序
            android.os.Process.killProcess(android.os.Process.myPid());
            System.exit(1);
        }
    }

    /**
     * 自定义错误处理,收集错误信息 发送错误报告等操作均在此完成.
     *
     * @param ex
     * @return true:如果处理了该异常信息;否则返回false.
     */
    private boolean handleException(Throwable ex) {
        if (ex == null) {
            return false;
        }
        // 使用Toast来显示异常信息
        new Thread() {
            @Override
            public void run() {
                Looper.prepare();
                Toast.makeText(sApplicationContext, "程序出现异常，即将退出～", Toast.LENGTH_SHORT).show();
                Looper.loop();
            }
        }.start();

        return true;
    }

    public static void setupSDKContext() {
        // 注意，必须在调用其它 ZegoAPI 之前调用此方法
        ZegoLiveRoom.setSDKContext(new ZegoLiveRoom.SDKContextEx() {
            @Override
            public long getLogFileSize() {
                return 10 * 1024 * 1024;    // 单个日志文件大小不超过 10M，取值范围为 [5M, 100M]
            }

            @Nullable
            @Override
            public String getSoFullPath() {
                return null;                // return null 表示使用默认方式加载 libzegoliveroom.so，此处可以返回 so 的绝对路径，用来指定从这个位置加载 libzegoliveroom.so，确保应用具备存取此路径的权限
            }

            @Nullable
            @Override
            public String getLogPath() {
                return null;        // return null 表示日志文件会存储到默认位置，如果返回非空，则将日志文件存储到该路径下，注意应用必须具备存取该目录的权限
            }

            @NonNull
            @Override
            public Application getAppContext() {
                return ZegoApplication.sApplicationContext;    // 必须返回当前应用的 Application 实例
            }

        });
    }
}
