package com.zego.livedemo5;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.support.annotation.NonNull;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.content.ContextCompat;
import android.support.v4.view.ViewPager;
import android.support.v7.widget.Toolbar;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;


import com.pgyersdk.update.PgyUpdateManager;
import com.tencent.tauth.Tencent;
import com.zego.livedemo5.ui.activities.AboutZegoActivity;
import com.zego.livedemo5.ui.activities.SettingActivity;
import com.zego.livedemo5.ui.activities.base.AbsBaseActivity;
import com.zego.livedemo5.ui.activities.base.AbsBaseFragment;
import com.zego.livedemo5.ui.fragments.PublishFragment;
import com.zego.livedemo5.ui.fragments.RoomListFragment;
import com.zego.livedemo5.ui.widgets.NavigationBar;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.livedemo5.utils.SystemUtil;

import java.util.ArrayList;
import java.util.List;

import butterknife.Bind;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class MainActivity extends AbsBaseActivity implements NavigationBar.NavigationBarListener {

    private List<AbsBaseFragment> mFragments;

    private FragmentPagerAdapter mPagerAdapter;

    private int mTabSelected;

    @Bind(R.id.toolbar)
    public Toolbar toolBar;


    private OnSetConfigsCallback mSetConfigsCallback;

    @Bind(R.id.nb)
    public NavigationBar navigationBar;

    @Bind(R.id.vp)
    public ViewPager viewPager;


    @Override
    protected int getContentViewLayout() {
        return R.layout.acvitity_main;
    }

    @Override
    protected void initExtraData(Bundle savedInstanceState) {

    }

    @Override
    protected void onResume() {
        super.onResume();
        updateTitle();
    }

    private RoomListFragment roomListFragment;
    private PublishFragment publishFragment;

    @Override
    protected void initVariables(Bundle savedInstanceState) {
        mTabSelected = 0;
        mFragments = new ArrayList<>();
        roomListFragment = RoomListFragment.newInstance();
        mFragments.add(roomListFragment);
        publishFragment = PublishFragment.newInstance();
        mFragments.add(publishFragment);

        mPagerAdapter = new FragmentPagerAdapter(getSupportFragmentManager()) {
            @Override
            public Fragment getItem(int position) {
                return mFragments.get(position);
            }

            @Override
            public int getCount() {
                return mFragments.size();
            }
        };

        mSetConfigsCallback = (OnSetConfigsCallback) getSupportFragmentManager().findFragmentById(R.id.setting_fragment);

        setSupportActionBar(toolBar);
        toolBar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, SettingActivity.class);
                startActivity(intent);
            }
        });

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mHandler != null) {
            mHandler.removeCallbacksAndMessages(null);
        }
    }

    @Override
    protected void initViews(Bundle savedInstanceState) {
        navigationBar.setNavigationBarListener(this);
        navigationBar.selectTab(0);

        viewPager.setAdapter(mPagerAdapter);
        viewPager.addOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {

            }

            @Override
            public void onPageSelected(int position) {
                mTabSelected = position;
                navigationBar.selectTab(position);
            }

            @Override
            public void onPageScrollStateChanged(int state) {

            }
        });


    }

    private final int CHECK_PERMISSIONS = 102;

    @Override
    protected void loadData(Bundle savedInstanceState) {

        if (checkOrRequestPermission(CHECK_PERMISSIONS)) {
            checkApkUpdate();
        }
    }

    private void checkApkUpdate() {
        if (checkOrRequestPermission(1002) && !SystemUtil.isDebugVersion(this)) {
            /** 可选配置集成方式 **/
            new PgyUpdateManager.Builder()
                    .setForced(false)                // 设置是否强制更新
                    .setUserCanRetry(false)         // 失败后是否提示重新下载
                    .setDeleteHistroyApk(false)     // 检查更新前是否删除本地历史 Apk， 默认为true
                    .register();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode) {
            case CHECK_PERMISSIONS: {
                boolean allPermissionGranted = true;
                for (int i = 0; i < grantResults.length; i++) {
                    if (grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                        allPermissionGranted = false;
                        Toast.makeText(this, String.format("获取%s权限失败 ", permissions[i]), Toast.LENGTH_LONG).show();
                    }
                }
                if (allPermissionGranted) {
                    checkApkUpdate();
                } else {
                    Intent intent = new Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS);
                    intent.setData(Uri.parse("package:" + this.getPackageName()));
                    startActivity(intent);
                }
                break;
            }
        }
    }

    private static String[] PERMISSIONS_STORAGE = {
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.WRITE_EXTERNAL_STORAGE"};


    private boolean checkOrRequestPermission(int code) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(this, "android.permission.READ_EXTERNAL_STORAGE") != PackageManager.PERMISSION_GRANTED ||
                    ContextCompat.checkSelfPermission(this, "android.permission.WRITE_EXTERNAL_STORAGE") != PackageManager.PERMISSION_GRANTED) {
                this.requestPermissions(PERMISSIONS_STORAGE, code);
                return false;
            }
        }
        return true;
    }

    @Override
    public void onTabSelect(int tabIndex) {
        mTabSelected = tabIndex;
        viewPager.setCurrentItem(tabIndex, true);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            exit();
            return false;
        }
        return super.onKeyDown(keyCode, event);
    }

    private void updateTitle() {
        long currentAppFlavor = PreferenceUtil.getInstance().getCurrentAppFlavor();
        String title = ZegoAppHelper.getAppTitle(currentAppFlavor, MainActivity.this);
        toolBar.setTitle(title);
    }

    /**
     * 用户连续点击两次返回键可以退出应用的时间间隔.
     */
    public static final long EXIT_INTERVAL = 1000;

    private long mBackPressedTime;

    /**
     * 退出.
     */
    private void exit() {
        /* 连按两次退出 */
        long currentTime = System.currentTimeMillis();
        if (currentTime - mBackPressedTime > EXIT_INTERVAL) {
            Toast.makeText(this, "再按一次退出程序", Toast.LENGTH_SHORT).show();
            mBackPressedTime = currentTime;
        } else {
            // 释放Zego sdk
            ZegoApiManager.getInstance().releaseSDK();
            System.exit(0);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        if (id == R.id.action_contact_us) {
            Tencent.createInstance("", MainActivity.this).startWPAConversation(MainActivity.this, "84328558", "");
            return true;
        }

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            AboutZegoActivity.actionStart(MainActivity.this);
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
    }

    public interface OnSetConfigsCallback {

        /**
         * Setting 页面关闭时调用
         *
         * @return < 0: 数据格式非法; 0: 无修改或者不需要重新初始化SDK; > 0: 需要重新初始化 SDK
         */
        int onSetConfig();


    }

    public interface OnReInitSDKCallback {

        /**
         * 当重新 initSDK 时调用
         */
        void onReInitSDK();
    }
}
