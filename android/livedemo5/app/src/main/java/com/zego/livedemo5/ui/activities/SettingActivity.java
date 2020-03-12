package com.zego.livedemo5.ui.activities;

import android.support.v4.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.FragmentActivity;

import com.zego.livedemo5.R;
import com.zego.livedemo5.ui.fragments.SettingFragment;

/**
 * Created by zego on 2018/9/10.
 */

public class SettingActivity extends FragmentActivity {

    SettingFragment fragment;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_setting);

        fragment = (SettingFragment) getSupportFragmentManager().findFragmentById(R.id.setting_fragment);

    }

    @Override
    public void finish() {
        super.finish();

        fragment.onSetConfig();
        fragment = null;
    }
}
