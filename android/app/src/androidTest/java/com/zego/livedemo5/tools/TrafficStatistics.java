package com.zego.livedemo5.tools;

import android.net.TrafficStats;

/**
 * Created by realuei on 2017/3/16.
 */

public final class TrafficStatistics extends AbstractRecorder {
    private int myUid = -1;
    private long beforeRxBytes, beforeTxBytes, afterRxBytes, afterTxBytes;
    private long beforeAppRxBytes, beforeAppTxBytes, afterAppRxBytes, afterAppTxBytes;



    public TrafficStatistics(int uid) {
        myUid = uid;
    }

    @Override
    public void beginRecord() {
        super.beginRecord();

        beforeRxBytes = TrafficStats.getTotalRxBytes();
        beforeTxBytes = TrafficStats.getTotalTxBytes();

        if (myUid > 0) {
            beforeAppRxBytes = TrafficStats.getUidRxBytes(myUid);
            beforeAppTxBytes = TrafficStats.getUidTxBytes(myUid);
        }
    }

    @Override
    public void stopRecord() {
        super.stopRecord();

        afterRxBytes = TrafficStats.getTotalRxBytes();
        afterTxBytes = TrafficStats.getTotalTxBytes();

        if (myUid > 0) {
            afterAppRxBytes = TrafficStats.getUidRxBytes(myUid);
            afterAppTxBytes = TrafficStats.getUidTxBytes(myUid);
        }
    }

    public float getTotalRxKBytes() {
        return (float)(afterRxBytes - beforeRxBytes) / 1024;
    }

    public float getTotalTxKBytes() {
        return (float)(afterTxBytes - beforeTxBytes) / 1024;
    }

    public float getAppTotalRxKBytes() {
        return (float)(afterAppRxBytes - beforeAppRxBytes) / 1024;
    }

    public float getAppTotalTxKBytes() {
        return (float)(afterAppTxBytes - beforeAppTxBytes) / 1024;
    }
}
