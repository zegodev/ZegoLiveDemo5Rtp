package com.zego.livedemo5.utils;

import com.zego.zegoliveroom.constants.ZegoBeauty;

/**
 * Copyright © 2017 Zego. All rights reserved.
 */

public class ZegoRoomUtil {

    public static final int ROOM_TYPE_SINGLE = 1;

    public static final int ROOM_TYPE_MORE = 2;

    public static final int ROOM_TYPE_MIX = 3;

    public static final int ROOM_TYPE_GAME = 4;

    public static final int ROOM_TYPE_WOLF = 5;

    public static final String ROOM_PREFIX_SINGLE_ANCHOR = "#d-";

    public static final String ROOM_PREFIX_MORE_ANCHORS = "#m-";

    public static final String ROOM_PREFIX_MIX_STREAM = "#s-";

    public static final String ROOM_PREFIX_GAME_LIVING = "#g-";

    public static final String ROOM_PREFIX_WERE_WOLVES = "#i-";


    public static String getRoomID(int roomType){
        String roomID = null;
        switch (roomType){
            case ROOM_TYPE_SINGLE:
                roomID = ROOM_PREFIX_SINGLE_ANCHOR;
                break;
            case ROOM_TYPE_MORE:
                roomID = ROOM_PREFIX_MORE_ANCHORS;
                break;
            case ROOM_TYPE_MIX:
                roomID = ROOM_PREFIX_MIX_STREAM;
                break;
            case ROOM_TYPE_GAME:
                roomID = ROOM_PREFIX_GAME_LIVING;
                break;
            case ROOM_TYPE_WOLF:
                roomID = ROOM_PREFIX_WERE_WOLVES;
                break;
        }

        return roomID + PreferenceUtil.getInstance().getUserID();
    }

    public static String getPublishStreamID(){
        return "s-" + PreferenceUtil.getInstance().getUserID() + "-" + System.currentTimeMillis();
    }

    public static int getZegoBeauty(int index){

        int beauty = 0;

        switch (index) {
            case 0:
                beauty = ZegoBeauty.NONE;
                break;
            case 1:
                beauty = ZegoBeauty.POLISH;
                break;
            case 2:
                beauty = ZegoBeauty.WHITEN;
                break;
            case 3:
                beauty = ZegoBeauty.POLISH | ZegoBeauty.WHITEN;
                break;
            case 4:
                beauty = ZegoBeauty.POLISH | ZegoBeauty.SKIN_WHITEN;
                break;
        }

        return beauty;
    }
}
