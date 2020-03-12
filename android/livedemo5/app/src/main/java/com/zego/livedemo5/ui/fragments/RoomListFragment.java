package com.zego.livedemo5.ui.fragments;

import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.zego.livedemo5.MainActivity;
import com.zego.livedemo5.R;
import com.zego.livedemo5.ZegoApiManager;
import com.zego.livedemo5.ZegoApplication;
import com.zego.livedemo5.presenters.BizLivePresenter;
import com.zego.livedemo5.ui.activities.gamelive.GameLivingPlayActivity;
import com.zego.livedemo5.ui.activities.mixstream.MixStreamPlayActivity;
import com.zego.livedemo5.ui.activities.moreanchors.MoreAnchorsPlayActivity;
import com.zego.livedemo5.ui.activities.singleanchor.SingleAnchorPlayActivity;
import com.zego.livedemo5.ui.activities.wolvesgame.WolvesGameInTurnActivity;
import com.zego.livedemo5.utils.ZegoRoomUtil;
import com.zego.livedemo5.ui.adapters.ListRoomAdapter;
import com.zego.livedemo5.ui.adapters.SpaceItemDecoration;
import com.zego.livedemo5.ui.activities.base.AbsBaseFragment;
import com.zego.support.RoomInfo;
import com.zego.support.RoomListUpdateListener;
import com.zego.zegoliveroom.callback.IZegoInitSDKCompletionCallback;

import java.util.ArrayList;

import butterknife.Bind;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class RoomListFragment extends AbsBaseFragment implements MainActivity.OnReInitSDKCallback, IZegoInitSDKCompletionCallback {

    @Bind(R.id.srl)
    public SwipeRefreshLayout swipeRefreshLayout;

    @Bind(R.id.rlv_room_list)
    public RecyclerView rlvRoomList;

    @Bind(R.id.tv_hint_pull_refresh)
    public TextView tvHintPullRefresh;

    private ArrayList<RoomInfo> mListRoom;

    private ListRoomAdapter mListRoomAdapter;

    private LinearLayoutManager mLinearLayoutManager;


    public static RoomListFragment newInstance() {
        return new RoomListFragment();
    }

    @Override
    protected int getContentViewLayout() {
        return R.layout.fragment_room_list;
    }

    @Override
    protected void initExtraData() {

    }

    @Override
    public void onInitSDK(int errorCode) {
        ZegoApplication.zgAppSupportApi.api().updateRoomList(ZegoApiManager.getInstance().getCurrentAppID());
    }

    @Override
    protected void initVariables() {

        mListRoom = new ArrayList<>();
        mListRoomAdapter = new ListRoomAdapter(mParentActivity, mListRoom);
        mListRoomAdapter.setHasMoreData(false);
        mListRoomAdapter.setOnItemClickListener(new ListRoomAdapter.OnItemClickListener() {
            @Override
            public void OnItemClick(View view, int position) {
                RoomInfo roomInfo = null;
                if (mListRoom != null) {
                    roomInfo = mListRoom.get(position);
                }

                if (roomInfo == null) {
                    return;
                }
                // 默认为多人连麦模式, 为了兼容老版本
                int publishType = 2;
                if (roomInfo.getRoomId().startsWith(ZegoRoomUtil.ROOM_PREFIX_SINGLE_ANCHOR)) {
                    publishType = 1;
                } else if (roomInfo.getRoomId().startsWith(ZegoRoomUtil.ROOM_PREFIX_MORE_ANCHORS)) {
                    publishType = 2;
                } else if (roomInfo.getRoomId().startsWith(ZegoRoomUtil.ROOM_PREFIX_MIX_STREAM)) {
                    publishType = 3;
                } else if (roomInfo.getRoomId().startsWith(ZegoRoomUtil.ROOM_PREFIX_GAME_LIVING)) {
                    publishType = 4;
                } else if (roomInfo.getRoomId().startsWith(ZegoRoomUtil.ROOM_PREFIX_WERE_WOLVES)) {
                    publishType = 5;
                }

                switch (publishType) {
                    case 1:
                        SingleAnchorPlayActivity.actionStart(mParentActivity, roomInfo);
                        break;
                    case 2:
                        MoreAnchorsPlayActivity.actionStart(getActivity(), roomInfo);
                        break;
                    case 3:
                        MixStreamPlayActivity.actionStart(getActivity(), roomInfo);
                        break;
                    case 4:
                        GameLivingPlayActivity.actionStart(mParentActivity, roomInfo);
                        break;
                    case 5:
                        WolvesGameInTurnActivity.actionStart(mParentActivity, roomInfo);
                        break;
                }

            }
        });
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        ZegoApplication.zgAppSupportApi.api().setRoomListUpdateListener(null);
        if (mHandler != null) {
            mHandler.removeCallbacksAndMessages(null);
        }
        if (swipeRefreshLayout != null) {
            swipeRefreshLayout.setOnRefreshListener(null);
        }
        if (mListRoomAdapter != null) {
            mListRoomAdapter.setOnItemClickListener(null);
        }
        if (rlvRoomList != null) {
            rlvRoomList.setAdapter(null);
        }

    }

    @Override
    protected void initViews() {
        mLinearLayoutManager = new LinearLayoutManager(mParentActivity);
        rlvRoomList.setLayoutManager(mLinearLayoutManager);
        rlvRoomList.addItemDecoration(new SpaceItemDecoration(mResources.getDimensionPixelSize(R.dimen.dimen_5)));

        ZegoApiManager.getInstance().setZegoInitSDKCompletionCallback(this);

        // 设置 进度条的颜色变化，最多可以设置4种颜色
        swipeRefreshLayout.setColorSchemeResources(android.R.color.holo_red_light, android.R.color.holo_blue_dark,
                android.R.color.holo_orange_dark, android.R.color.holo_orange_dark);

        ZegoApplication.zgAppSupportApi.api().setRoomListUpdateListener(new RoomListUpdateListener() {
            @Override
            public void onUpdateRoomList(ArrayList<RoomInfo> listRoom) {
                mListRoom.clear();
                for (com.zego.support.RoomInfo roomInfo : listRoom) {

                    mListRoom.add(roomInfo);

                }
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (mListRoom.size() == 0) {
                            tvHintPullRefresh.setVisibility(View.VISIBLE);
                        } else {
                            tvHintPullRefresh.setVisibility(View.INVISIBLE);
                        }
                        mListRoomAdapter.notifyDataSetChanged();
                        swipeRefreshLayout.setRefreshing(false);
                    }
                });
            }

            @Override
            public void onUpdateRoomListError() {
                swipeRefreshLayout.setRefreshing(false);
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(RoomListFragment.this.getActivity(), getString(R.string.request_room_list_failure), Toast.LENGTH_LONG).show();
                    }
                });
            }
        });

        swipeRefreshLayout.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                // 通知数据变化
                mListRoomAdapter.notifyDataSetChanged();
                // 下拉刷新, 数据清零
                mListRoom.clear();
                BizLivePresenter.getInstance().getRoomList();
            }
        });

        BizLivePresenter.getInstance().getRoomList();

        rlvRoomList.setAdapter(mListRoomAdapter);

    }

    @Override
    protected void loadData() {
        swipeRefreshLayout.post(new Runnable() {
            @Override
            public void run() {
                swipeRefreshLayout.setRefreshing(true);
                BizLivePresenter.getInstance().getRoomList();
            }
        });
    }

    /**
     * @see MainActivity.OnReInitSDKCallback#onReInitSDK()
     */
    @Override
    public void onReInitSDK() {
        mListRoom.clear();

        BizLivePresenter.getInstance().getRoomList();
    }
}
