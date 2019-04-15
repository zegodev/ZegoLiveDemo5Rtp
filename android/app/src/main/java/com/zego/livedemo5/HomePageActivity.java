package com.zego.livedemo5;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;

import com.zego.zegoliveroom.callback.IZegoInitSDKCompletionCallback;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class HomePageActivity extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ZegoApiManager.getInstance().setZegoInitSDKCompletionCallback(new IZegoInitSDKCompletionCallback() {
            @Override
            public void onInitSDK(int i) {
                Intent intent = new Intent(HomePageActivity.this, MainActivity.class);
                startActivity(intent);
                finish();
            }
        });

        ZegoApiManager.getInstance().initSDK();
    }

    @Override
    public void finish() {
        super.finish();
        ZegoApiManager.getInstance().setZegoInitSDKCompletionCallback(null);
    }
}
