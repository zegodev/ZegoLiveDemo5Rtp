package com.zego.livedemo5.ui.activities.wolvesgame;

/**
 * 推流模式
 *
 * Created by realuei on 2017/6/9.
 */

public enum PublishMode {
    /**通过CDN推流*/
    Low_Cost,
    /**推流时不走CDN，此模式暂不支持，由 Super_Low_Delay 替代*/
    Low_Delay,
    /** 超低成本(推流时不走CDN；且停止说话时，不中断推流) */
    Super_Low_Delay,
}
