package com.zego.livedemo5.presenters;


import com.zego.livedemo5.ZegoApiManager;
import com.zego.livedemo5.ZegoApplication;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


/**
 * des: 为了更好的展示zego的直播技术, 我们开发了简单的业务测功能, 主要用于管理用户信息、 流信息,
 * 类似于zego客户的业务逻辑.
 */
public class BizLivePresenter {

    private static BizLivePresenter sInstance;

    /**
     * 线程池.
     */
    private ExecutorService mExecutorService;


    private BizLivePresenter() {
        mExecutorService = Executors.newFixedThreadPool(4);
    }

    public static BizLivePresenter getInstance() {
        if (sInstance == null) {
            synchronized (BizLivePresenter.class) {
                if (sInstance == null) {
                    sInstance = new BizLivePresenter();
                }
            }
        }
        return sInstance;
    }



    /**
     * 获取房间列表.
     */
    public void getRoomList() {
        mExecutorService.execute(new Runnable() {
            @Override
            public void run() {
                long appID = ZegoApiManager.getInstance().getCurrentAppID();
                ZegoApplication.zgAppSupportApi.api().updateRoomList(appID);
            }
        });
    }
}