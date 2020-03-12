package com.zego.livedemo5.ui.activities;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;


import com.zego.livedemo5.R;
import com.zego.livedemo5.ui.adapters.LogListAdapter;
import com.zego.livedemo5.ui.activities.base.AbsBaseActivity;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.livedemo5.utils.ShareUtils;

import java.util.LinkedList;

import butterknife.Bind;
import butterknife.OnClick;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class LogListActivity extends AbsBaseActivity {

    public static final String KEY_LIST_LOG = "KEY_LIST_LOG";


    @Bind(R.id.recyclerView)
    public RecyclerView recyclerView;

    private LogListAdapter mLogListAdapter;

    private LinkedList<String> mLinkedListData;

    private PreferenceUtil.OnChangeListener mOnChangeListener;

    public static void actionStart(Activity activity){
        Intent intent = new Intent(activity, LogListActivity.class);
        activity.startActivity(intent);
    }
    @Override
    protected int getContentViewLayout() {
        return R.layout.activity_log_list;
    }

    @Override
    protected void initExtraData(Bundle savedInstanceState) {

    }

    @Override
    protected void initVariables(Bundle savedInstanceState) {
        mLinkedListData = (LinkedList<String>) PreferenceUtil.getInstance().getObjectFromString(KEY_LIST_LOG);
        if (mLinkedListData == null) {
            mLinkedListData = new LinkedList<>();
        }
        mOnChangeListener = new PreferenceUtil.OnChangeListener() {
            @Override
            public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
                if (KEY_LIST_LOG.equals(key)) {
                    mLinkedListData.clear();
                    LinkedList<String> data = (LinkedList<String>) PreferenceUtil.getInstance().getObjectFromString(KEY_LIST_LOG);
                    if (data != null) {
                        mLinkedListData.addAll(data);
                    }
                    mLogListAdapter.notifyDataSetChanged();
                }
            }
        };
        PreferenceUtil.getInstance().registerOnChangeListener(mOnChangeListener);
    }

    @Override
    protected void initViews(Bundle savedInstanceState) {
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        mLogListAdapter = new LogListAdapter(this, mLinkedListData);
        recyclerView.setAdapter(mLogListAdapter);
    }

    @Override
    protected void loadData(Bundle savedInstanceState) {

    }

    @OnClick(R.id.tv_back)
    public void back(){
        PreferenceUtil.getInstance().unregisterOnChangeListener(mOnChangeListener);
        finish();
    }
}
