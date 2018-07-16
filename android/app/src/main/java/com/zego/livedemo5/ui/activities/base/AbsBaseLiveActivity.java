package com.zego.livedemo5.ui.activities.base;

import android.app.ProgressDialog;
import android.content.res.Resources;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.WindowManager;

import com.zego.livedemo5.ui.activities.LogListActivity;
import com.zego.livedemo5.utils.PreferenceUtil;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedList;

import butterknife.ButterKnife;


/**
 * des: activity 基类
 */
public abstract class AbsBaseLiveActivity extends AppCompatActivity {

    protected Resources mResources;

    protected Handler mHandler;

    protected ProgressDialog mProgressDialog;

    protected LinkedList<String> mListLog = new LinkedList<>();

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
    protected abstract void doBusiness(Bundle savedInstanceState);

    /**
     * Handler 处理类，当子类需要处理 mHandler 的消息时，可以重写此方法
     * @return 处理
     */
    protected Handler.Callback getHandlerCallback() {
        return null;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // 禁止手机休眠
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        setContentView(getContentViewLayout());

        // 初始化butternife
        ButterKnife.bind(this);

        initExtraData(savedInstanceState);
        initBaseVariables();
        initVariables(savedInstanceState);

        initViews(savedInstanceState);
        doBusiness(savedInstanceState);

    }



    /**
     * 初始化基类中的变量.
     */
    private void initBaseVariables() {
        mResources = getResources();
        mHandler = new Handler(getHandlerCallback());
        mProgressDialog = new ProgressDialog(this);
        mProgressDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
    }

    static private SimpleDateFormat sDataFormat = new SimpleDateFormat("[hh:mm:ss.SSS]");
    protected void recordLog(String msg) {
        String now = sDataFormat.format(new Date());
        mListLog.addFirst(String.format("%s %s", now, msg));
        PreferenceUtil.getInstance().setObjectToString(LogListActivity.KEY_LIST_LOG, mListLog);
    }

    protected void recordLog(String msgFormat, Object... args) {
        String message = String.format(msgFormat, args);
        recordLog(message);
    }

}
