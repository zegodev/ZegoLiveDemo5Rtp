package com.zego.livedemo5.ui.activities.gamelive;

import android.app.Activity;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.TextureView;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;

import com.zego.livedemo5.R;
import com.zego.livedemo5.ZegoApiManager;
import com.zego.livedemo5.constants.IntentExtra;
import com.zego.livedemo5.presenters.RoomInfo;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.callback.IZegoLivePlayerCallback;
import com.zego.zegoliveroom.callback.IZegoLoginCompletionCallback;
import com.zego.zegoliveroom.callback.IZegoRoomCallback;
import com.zego.zegoliveroom.constants.ZegoConstants;
import com.zego.zegoliveroom.constants.ZegoVideoViewMode;
import com.zego.zegoliveroom.entity.ZegoStreamQuality;
import com.zego.zegoliveroom.entity.ZegoStreamInfo;

/**
 * Copyright © 2016 Zego. All rights reserved.
 */

public class GameLivingPlayActivity extends AppCompatActivity {

    public static final String TAG = GameLivingPlayActivity.class.getSimpleName();

    private TextureView mTextureView;

    private String mRoomID;

    private String mPlayStreamID;

    private ZegoLiveRoom mZegoLiveRoom;


    /**
     * 启动入口.
     *
     * @param activity 源activity
     * @param roomInfo 房间信息
     */
    public static void actionStart(Activity activity, RoomInfo roomInfo) {
        Intent intent = new Intent(activity, GameLivingPlayActivity.class);
        intent.putExtra(IntentExtra.ROOM_ID, roomInfo.room_id);
        activity.startActivity(intent);
        activity.overridePendingTransition(R.anim.scale_translate,
                R.anim.my_alpha_action);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //取消标题栏
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        //取消状态栏
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);

        setContentView(R.layout.activity_gameliving_play);

        if (savedInstanceState == null) {
            Intent intent = getIntent();
            mRoomID = intent.getStringExtra(IntentExtra.ROOM_ID);
        }

        mTextureView = (TextureView) findViewById(R.id.textureView);

        mZegoLiveRoom = ZegoApiManager.getInstance().getZegoLiveRoom();

        initCallback();

        mZegoLiveRoom.loginRoom(mRoomID, ZegoConstants.RoomRole.Audience, new IZegoLoginCompletionCallback() {
            @Override
            public void onLoginCompletion(int stateCode, ZegoStreamInfo[] zegoStreamInfos) {
                if(stateCode == 0){

                    Log.i(TAG, "登陆房间成功");

                    if(zegoStreamInfos != null && zegoStreamInfos.length > 0){
                        mPlayStreamID = zegoStreamInfos[0].streamID;
                        startPlay();
                    }
                }else {
                    Log.i(TAG, "登陆房间失败");
                    Toast.makeText(GameLivingPlayActivity.this, "登陆房间失败", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }


    private void initCallback() {
        mZegoLiveRoom.setZegoLivePlayerCallback(new IZegoLivePlayerCallback() {
            @Override
            public void onPlayStateUpdate(int stateCode, String streamID) {
                // 拉流状态更新
                if (stateCode == 0) {
                    Toast.makeText(GameLivingPlayActivity.this, "播放成功", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(GameLivingPlayActivity.this, "播放失败", Toast.LENGTH_SHORT).show();
                }
            }

            @Override
            public void onPlayQualityUpdate(String s, ZegoStreamQuality streamQuality) {

            }

            @Override
            public void onInviteJoinLiveRequest(int seq, String fromUserID, String fromUserName, String roomID) {

            }

            @Override
            public void onRecvEndJoinLiveCommand(String fromUserId, String fromUserName, String roomId) {
                Toast.makeText(GameLivingPlayActivity.this, String.format("onRecvEndJoinLiveCommand, from userId: %s, from userName: %s, roomId: %s", fromUserId, fromUserName, roomId), Toast.LENGTH_LONG).show();
            }

            @Override
            public void onVideoSizeChangedTo(String streamID, int width, int height) {
            }
        });

        mZegoLiveRoom.setZegoRoomCallback(new IZegoRoomCallback() {
            @Override
            public void onKickOut(int i, String s) {

            }

            @Override
            public void onDisconnect(int i, String s) {

            }

            @Override
            public void onReconnect(int i, String s) {

            }

            @Override
            public void onTempBroken(int i, String s) {

            }

            @Override
            public void onStreamUpdated(int type, ZegoStreamInfo[] zegoStreamInfos, String s) {
                if(zegoStreamInfos != null && zegoStreamInfos.length > 0){
                    mPlayStreamID = zegoStreamInfos[0].streamID;
                    if(type == ZegoConstants.StreamUpdateType.Added){
                        startPlay();
                    }else if(type == ZegoConstants.StreamUpdateType.Deleted){
                        stopPlay();
                    }
                }
            }

            @Override
            public void onStreamExtraInfoUpdated(ZegoStreamInfo[] zegoStreamInfos, String s) {

            }

            @Override
            public void onRecvCustomCommand(String s, String s1, String s2, String s3) {

            }
        });
    }


    protected void startPlay() {
        mTextureView.setVisibility(View.VISIBLE);
        mTextureView.invalidate();
        mZegoLiveRoom.setViewMode(ZegoVideoViewMode.ScaleAspectFill, mPlayStreamID);
        mZegoLiveRoom.startPlayingStream(mPlayStreamID, mTextureView);
    }

    protected void stopPlay() {
        mTextureView.invalidate();
        mTextureView.setVisibility(View.INVISIBLE);
        mZegoLiveRoom.stopPlayingStream(mPlayStreamID);
    }

    private void logout() {
        mZegoLiveRoom.updatePlayView(mPlayStreamID, null);
        mZegoLiveRoom.stopPlayingStream(mPlayStreamID);
        mZegoLiveRoom.setZegoLivePlayerCallback(null);
        mZegoLiveRoom.logoutRoom();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        logout();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        int currentOrientation = getWindowManager().getDefaultDisplay().getRotation();
        mZegoLiveRoom.setViewRotation(currentOrientation, mPlayStreamID);
    }
}
