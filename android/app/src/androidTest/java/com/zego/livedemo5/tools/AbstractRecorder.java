package com.zego.livedemo5.tools;

import java.util.Calendar;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Created by realuei on 2017/3/16.
 */

public abstract class AbstractRecorder implements IRecorder {
    private Calendar beginTime, endTime;

    private AtomicBoolean isRecoding = new AtomicBoolean(false);

    public void beginRecord() {
        if (isRecoding.getAndSet(true)) {
            isRecoding.set(false);
            throw new RuntimeException("is recoding, stopRecord before the operation");
        }

        beginTime = Calendar.getInstance();
    }
    public void stopRecord() {
        if (!isRecoding.getAndSet(false)) throw new RuntimeException("has stop or not start");

        endTime = Calendar.getInstance();
    }

    @SuppressWarnings("unused")
    public Calendar getBeginTime() {
        return beginTime;
    }

    @SuppressWarnings("unused")
    public Calendar getEndTime() {
        return endTime;
    }

    @SuppressWarnings("unused")
    public long getUsedTimeInSeconds() {
        return (endTime.getTimeInMillis() - beginTime.getTimeInMillis()) / 1000;
    }

}
