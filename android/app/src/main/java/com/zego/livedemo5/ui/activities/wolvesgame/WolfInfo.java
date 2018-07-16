package com.zego.livedemo5.ui.activities.wolvesgame;

import com.zego.zegoliveroom.entity.ZegoUser;

/**
 * Created by realuei on 2017/5/10.
 */

public class WolfInfo extends ZegoUser {
    private String streamId;
    private int index;
    private SpeakingState state = SpeakingState.isIdle;

    public enum SpeakingState {
        /** 清闲 */
        isIdle(0),
        /** 允许说话 */
        allowSpeaking(1),
        /** 正在说话 */
        isSpeaking(2);

        private int value = 0;

        SpeakingState(int value) {
            this.value = value;
        }

        public int intValue() {
            return this.value;
        }

        static public SpeakingState valueOf(int value) {
            if (value < SpeakingState.values().length) {
                return SpeakingState.values()[value];
            }
            return isIdle;
        }
    }

    public WolfInfo(String userId, String userName) {
        this.userID = userId;
        this.userName = userName;
    }

    public WolfInfo(ZegoUser zegoUser) {
        this.userID = zegoUser.userID;
        this.userName = zegoUser.userName;
    }

    public String getUserId() {
        return userID;
    }

    public void setUserId(String userId) {
        this.userID = userId;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getStreamId() {
        return streamId;
    }

    public void setStreamId(String streamId) {
        this.streamId = streamId;
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }

    public SpeakingState getState() {
        return state;
    }

    public void setState(SpeakingState state) {
        this.state = state;
    }

    public void update(WolfInfo wolf) {
        if (wolf != null) {
            this.userID = wolf.userID;
            this.userName = wolf.userName;
            this.streamId = wolf.streamId;
            this.index = wolf.index;
            this.state = wolf.state;
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof WolfInfo)) return false;

        return this.userID.equals(((WolfInfo)obj).userID);
    }
}
