package com.zego.livedemo5.entities;

import com.zego.zegoliveroom.constants.ZegoVideoViewMode;

import java.util.ArrayList;
import java.util.List;

/**
 * Copyright © 2017 Zego. All rights reserved.
 */
public class ZegoStream {

    public enum StreamType {
        Publish,
        Play
    }

    private int mLiveQuality = 0;

    private int mZegoVideoViewMode = ZegoVideoViewMode.ScaleAspectFill;

    private List<String> mListShareUrls = new ArrayList<>();

    private boolean mNeedToSwitchFullScreen = false;

    private String mStreamID = null;

    private StreamType mStreamType = null;


    public int getLiveQuality() {
        return mLiveQuality;
    }

    public void setLiveQuality(int liveQuality) {
        mLiveQuality = liveQuality;
    }

    public int getZegoVideoViewMode() {
        return mZegoVideoViewMode;
    }

    public void setZegoVideoViewMode(int zegoVideoViewMode) {
        mZegoVideoViewMode = zegoVideoViewMode;
    }

    public List<String> getListShareUrls() {
        return mListShareUrls;
    }

    public void setListShareUrls(List<String> listShareUrls) {
        mListShareUrls = listShareUrls;
    }

    public boolean isNeedToSwitchFullScreen() {
        return mNeedToSwitchFullScreen;
    }

    public void setNeedToSwitchFullScreen(boolean needToSwitchFullScreen) {
        mNeedToSwitchFullScreen = needToSwitchFullScreen;
    }

    public String getStreamID() {
        return mStreamID;
    }

    public void setStreamID(String streamID) {
        mStreamID = streamID;
    }

    public StreamType getStreamType() {
        return mStreamType;
    }

    public void setStreamType(StreamType streamType) {
        mStreamType = streamType;
    }
}
