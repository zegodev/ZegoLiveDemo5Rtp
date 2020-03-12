package com.zego.livedemo5.callback;

/**
 * Created by zego on 2018/6/1.
 * 屏幕方向回调类
 */

public interface LiveDirectionCallback{
    /**
     * 屏幕方向
     * @param rotating 屏幕角度
     */
    void screenDirection(int rotating);
}