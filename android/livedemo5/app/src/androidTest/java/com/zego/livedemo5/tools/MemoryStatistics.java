package com.zego.livedemo5.tools;

import android.os.Debug;

import java.util.ArrayList;
import java.util.List;

import static com.zego.livedemo5.tools.CommonTools.sleep;

/**
 * Created by realuei on 2017/3/16.
 */

public final class MemoryStatistics extends AbstractRecorder {

    public static class MemoryInfo {
        /** 虚拟耗用内存 */
        private long vss;
        /** 包含全部进程共享库的内存在内的物理内存 */
        private long rss;
        /** 包含部分进程共享库的内存在内的物理内存（其中部分进程共享库的内存大小按共享库的进程数进行等比例划分得出） */
        private long pss;
        /** 本进程正在使用的实际物理内存 */
        private long uss;
    }

    private long maxMemoryUsage;
    private List<MemoryInfo> memoryINfos = new ArrayList<>();

    @Override
    public void beginRecord() {
        super.beginRecord();

        new Thread(new Runnable() {
            @Override
            public void run() {

                sleep(1000);
            }
        }).start();
    }

    @Override
    public void stopRecord() {
        super.stopRecord();
    }


    private MemoryInfo getCurrentMemoryInfo() {
        Debug.MemoryInfo memoryInfo = new Debug.MemoryInfo();
        android.os.Debug.getMemoryInfo(memoryInfo);
        int ussMemory = memoryInfo.getTotalPrivateDirty();
        return null;
    }

}
