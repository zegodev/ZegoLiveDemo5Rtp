package com.zego.livedemo5.ui.activities.base;

import android.app.ProgressDialog;
import android.content.res.Resources;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;

import com.zego.livedemo5.ZegoApplication;

import butterknife.ButterKnife;


/**
 * des: activity 基类
 */
public abstract class AbsBaseActivity extends AppCompatActivity {

    protected Resources mResources;

    protected Handler mHandler;

    protected ProgressDialog mProgressDialog;

    /**
     * 获取内容页面的布局.
     *
     * @return 返回内容页面的布局
     */
    protected abstract int getContentViewLayout();

    /**
     * 初始化从外部传递过来的数据.
     */
    protected abstract void initExtraData(Bundle savedInstanceState);

    /**
     * 初始化子类中的变量.
     */
    protected abstract void initVariables(Bundle savedInstanceState);

    /**
     * 初始化子类中的控件.
     */
    protected abstract void initViews(Bundle savedInstanceState);

    /**
     * 加载数据.
     */
    protected abstract void loadData(Bundle savedInstanceState);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(getContentViewLayout());

        // 初始化butternife
        ButterKnife.bind(this);

        initExtraData(savedInstanceState);
        initBaseVariables();
        initVariables(savedInstanceState);
        initViews(savedInstanceState);
        loadData(savedInstanceState);
    }

    /**
     * 初始化基类中的变量.
     */
    private void initBaseVariables() {
        mResources = getResources();
        mHandler = new Handler();
        mProgressDialog = new ProgressDialog(this);
        mProgressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
    }


}
