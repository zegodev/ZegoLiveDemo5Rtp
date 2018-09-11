package com.zego.livedemo5.interfaces;


import com.android.volley.VolleyError;
import com.zego.livedemo5.presenters.RoomInfo;

import java.util.List;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */

public interface OnUpdateRoomListListener {
    void onUpdateRoomList(List<RoomInfo> listRoom);

    void onError(VolleyError error);
}
