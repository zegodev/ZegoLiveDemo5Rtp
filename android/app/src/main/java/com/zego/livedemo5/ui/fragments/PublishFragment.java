package com.zego.livedemo5.ui.fragments;

import android.Manifest;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.graphics.Rect;
import android.hardware.SensorManager;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.text.TextUtils;
import android.util.Log;
import android.view.OrientationEventListener;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.ToggleButton;


import com.zego.livedemo5.MainActivity;
import com.zego.livedemo5.R;
import com.zego.livedemo5.ZegoApiManager;
import com.zego.livedemo5.callback.LiveDirectionCallback;
import com.zego.livedemo5.ui.activities.gamelive.GameLiveActivity;
import com.zego.livedemo5.ui.activities.mixstream.MixStreamPublishActivity;
import com.zego.livedemo5.ui.activities.moreanchors.MoreAnchorsPublishActivity;
import com.zego.livedemo5.ui.activities.base.AbsBaseFragment;
import com.zego.livedemo5.ui.activities.singleanchor.SingleAnchorPublishActivity;
import com.zego.livedemo5.ui.activities.wolvesgame.WolvesGameHostActivity;
import com.zego.livedemo5.ui.widgets.DialogSelectPublishMode;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.livedemo5.utils.SystemUtil;
import com.zego.livedemo5.utils.ZegoRoomUtil;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.constants.ZegoAvConfig;
import com.zego.zegoliveroom.constants.ZegoVideoViewMode;


import butterknife.Bind;
import butterknife.OnClick;

import static android.content.Context.INPUT_METHOD_SERVICE;
import static android.view.Surface.ROTATION_0;
import static android.view.Surface.ROTATION_270;

/**
 * Copyright © 2016 Zego. All rights reserved.
 * des:
 */
public class PublishFragment extends AbsBaseFragment implements MainActivity.OnReInitSDKCallback {

    @Bind(R.id.tb_enable_front_cam)
    public ToggleButton tbEnableFrontCam;

    @Bind(R.id.tb_enable_torch)
    public ToggleButton tbEnableTorch;

    @Bind(R.id.sp_filters)
    public Spinner spFilters;

    @Bind(R.id.sp_beauties)
    public Spinner spBeauties;

    @Bind(R.id.et_publish_title)
    public EditText etPublishTitle;

    @Bind(R.id.textureView)
    public TextureView textureView;

    private int mSelectedBeauty = 0;

    private int mSelectedFilter = 0;

    private ZegoLiveRoom mZegoLiveRoom;

    private boolean mHasBeenCreated = false;

    private boolean mIsVisibleToUser = false;

    private boolean mSpinnerOfBeautyInitialed = false;

    private boolean mSpinnerOfFilterInitialed = false;

    public static PublishFragment newInstance() {
        return new PublishFragment();
    }

    @Override
    protected int getContentViewLayout() {
        return R.layout.fragment_publish;
    }

    @Override
    protected void initExtraData() {

    }

    @Override
    protected void initVariables() {
        mZegoLiveRoom = ZegoApiManager.getInstance().getZegoLiveRoom();
    }

    @Override
    protected void initViews() {


        ArrayAdapter<String> beautyAdapter = new ArrayAdapter<>(mParentActivity, R.layout.item_spinner, mResources.getStringArray(R.array.beauties));
        spBeauties.setAdapter(beautyAdapter);
        spBeauties.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                mSelectedBeauty = position;
                if (mSpinnerOfBeautyInitialed) {
                    mZegoLiveRoom.enableBeautifying(ZegoRoomUtil.getZegoBeauty(position));
                } else {
                    mSpinnerOfBeautyInitialed = true;
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
        // 默认"全屏+美白"
        spBeauties.setSelection(3);

        ArrayAdapter<String> filterAdapter = new ArrayAdapter<>(mParentActivity, R.layout.item_spinner, mResources.getStringArray(R.array.filters));
        spFilters.setAdapter(filterAdapter);
        spFilters.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                mSelectedFilter = position;

                if (mSpinnerOfFilterInitialed) {
                    mZegoLiveRoom.setFilter(mSelectedFilter);
                } else {
                    mSpinnerOfFilterInitialed = true;
                }

            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });


        // 开启前置摄像头时, 手电筒不可用
        if (tbEnableFrontCam.isChecked()) {
            tbEnableTorch.setEnabled(false);
        }
        tbEnableFrontCam.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                mZegoLiveRoom.setFrontCam(isChecked);

                // 开启前置摄像头时, 手电筒不可用
                if (isChecked) {
                    mZegoLiveRoom.enableTorch(false);
                    tbEnableTorch.setChecked(false);
                    tbEnableTorch.setEnabled(false);
                } else {
                    tbEnableTorch.setEnabled(true);
                }
            }
        });

        tbEnableTorch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                mZegoLiveRoom.enableTorch(isChecked);
            }
        });


        mOrientationListener = new OrientationEventListener(this.getActivity(),
                SensorManager.SENSOR_DELAY_NORMAL) {

            @Override
            public void onOrientationChanged(int orientation) {

                if (orientation == OrientationEventListener.ORIENTATION_UNKNOWN) {
                    return;  //手机平放时，检测不到有效的角度
                }

                int orientation_;
                //只检测是否有四个角度的改变
                if (orientation > 335 || orientation < 30) { //0度
                    orientation_ = 0;
                    rotation = Surface.ROTATION_0;
                } else if (orientation > 65 && orientation < 120) { //90度
                    orientation_ = 90;
                    rotation = Surface.ROTATION_270;
                } else if (orientation > 155 && orientation < 210) { //180度
                    orientation_ = 180;
                    rotation = Surface.ROTATION_180;
                } else if (orientation > 245 && orientation < 300) { //270度
                    orientation_ = 270;
                    rotation = Surface.ROTATION_90;
                } else {
                    return;
                }

                if (mOrientation != orientation_) {
                    mOrientation = orientation_;
                    spBeauties.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            if (isRun) {
                                stopPreview();
                                initPreview();
                            }

                            int currentOrientation = mParentActivity.getWindowManager().getDefaultDisplay().getRotation();
                            // 设置app朝向
                            mZegoLiveRoom.setAppOrientation(currentOrientation);
                        }
                    }, 900);
                }
            }
        };

        if (mOrientationListener.canDetectOrientation()) {

            mOrientationListener.enable();
        } else {

            mOrientationListener.disable();
        }

    }


    private int rotation;
    private volatile int mOrientation = -1;

    OrientationEventListener mOrientationListener;

    @Override
    protected void loadData() {

    }

    @Override
    public void onResume() {
        super.onResume();
        isRun = true;
        if (mHasBeenCreated) {
            if (mIsVisibleToUser) {
                initPreview();
            }
        } else {
            mHasBeenCreated = true;
        }

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mHandler != null) {
            mHandler.removeCallbacksAndMessages(null);
            tbEnableTorch.setOnCheckedChangeListener(null);
            spFilters.setOnItemSelectedListener(null);
            spBeauties.setOnItemClickListener(null);
            tbEnableFrontCam.setOnCheckedChangeListener(null);
            tbEnableTorch.setOnCheckedChangeListener(null);
            tbEnableFrontCam.setOnCheckedChangeListener(null);
            mDialogSelectPublishMode = null;
        }
        if (mOrientationListener != null) {
            mOrientationListener.disable();
        }

    }

    private volatile boolean isRun = true;

    @Override
    public void onStop() {
        super.onStop();
        isRun = false;
    }

    @Override
    public void onPause() {
        super.onPause();

        stopPreview();
    }

    final DialogSelectPublishMode dialog = new DialogSelectPublishMode();

    @OnClick(R.id.btn_start_publish)
    public void startPublishing() {

        String publishTitle = etPublishTitle.getText().toString();
        if (TextUtils.isEmpty(publishTitle)) {
            publishTitle = "Hello-" + PreferenceUtil.getInstance().getUserName();
        }

        hideInputWindow();

        publishTitleTemp = publishTitle;

        dialog.setOnSelectPublishModeListener(mDialogSelectPublishMode);

        dialog.show(mParentActivity.getFragmentManager(), "selectPublishModeDialog");
    }

    String publishTitleTemp;

    DialogSelectPublishMode.OnSelectPublishModeListener mDialogSelectPublishMode = new DialogSelectPublishMode.OnSelectPublishModeListener() {
        @Override
        public void onSingleAnchorSelect() {
            SingleAnchorPublishActivity.actionStart(mParentActivity, publishTitleTemp, tbEnableFrontCam.isChecked(), tbEnableTorch.isChecked(), mSelectedBeauty, mSelectedFilter, mParentActivity.getWindowManager().getDefaultDisplay().getRotation());
        }

        @Override
        public void onMoreAnchorsSelect() {
            MoreAnchorsPublishActivity.actionStart(mParentActivity, publishTitleTemp, tbEnableFrontCam.isChecked(), tbEnableTorch.isChecked(), mSelectedBeauty, mSelectedFilter, mParentActivity.getWindowManager().getDefaultDisplay().getRotation());
        }

        @Override
        public void onMixStreamSelect() {
            MixStreamPublishActivity.actionStart(mParentActivity, publishTitleTemp, tbEnableFrontCam.isChecked(), tbEnableTorch.isChecked(), mSelectedBeauty, mSelectedFilter, mParentActivity.getWindowManager().getDefaultDisplay().getRotation());
        }

        @Override
        public void onGameLivingSelect() {
            LiveDirectionCallback liveDirection = new LiveDirectionCallback() {
                @Override
                public void screenDirection(int rotating) {
                    GameLiveActivity.actionStart(mParentActivity, publishTitleTemp, rotating);
                }
            };
            dialogList(liveDirection);
        }

        @Override
        public void onWolvesGameSelect() {
            WolvesGameHostActivity.actionStart(mParentActivity, publishTitleTemp, mParentActivity.getWindowManager().getDefaultDisplay().getRotation());
        }
    };


    private void dialogList(final LiveDirectionCallback liveDirection) {
        final String items[] = {getString(R.string.landscape_mode), getString(R.string.portrait_mode)};

        AlertDialog.Builder builder = new AlertDialog.Builder(this.getContext(), 3);
        builder.setTitle(R.string.select_capture_orientation);

        builder.setItems(items, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                if (which == 0) {
                    liveDirection.screenDirection(ROTATION_270);
                } else {
                    liveDirection.screenDirection(ROTATION_0);
                }
            }
        });
        builder.setPositiveButton(R.string.No, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
                dialog.cancel();
            }
        });
        builder.create().show();
    }


    @OnClick(R.id.main_content)
    public void hideInputWindow() {
        InputMethodManager imm = (InputMethodManager) mParentActivity.getSystemService(INPUT_METHOD_SERVICE);
        if (imm != null && imm.isActive()) {
            imm.hideSoftInputFromWindow(etPublishTitle.getWindowToken(), 0);
        }
    }

    @Override
    public void setUserVisibleHint(boolean isVisibleToUser) {
        super.setUserVisibleHint(isVisibleToUser);
        mIsVisibleToUser = isVisibleToUser;
        if (mHasBeenCreated) {
            if (isVisibleToUser) {
                startPreview();
            } else {
                stopPreview();
            }
        }
    }


    private void startPreview(){
        // 6.0及以上的系统需要在运行时申请CAMERA RECORD_AUDIO权限
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(mParentActivity, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED
                    || ContextCompat.checkSelfPermission(mParentActivity, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(mParentActivity, new String[]{
                        Manifest.permission.CAMERA, Manifest.permission.RECORD_AUDIO}, 102);
            } else {
                initPreview();
            }
        } else {
            initPreview();
        }
    }


    private void initPreview() {

        ZegoAvConfig config = ZegoApiManager.getInstance().getZegoAvConfig();
        // 获取屏幕比例
        boolean proportion = SystemUtil.getResolutionProportion(mParentActivity);
        if ((proportion && config.getVideoCaptureResolutionWidth() < config.getVideoCaptureResolutionHeight()) ||
                (!proportion && config.getVideoCaptureResolutionWidth() > config.getVideoCaptureResolutionHeight())) {
            // 如果不为横屏比例, 则切换分辨率
            int height = config.getVideoCaptureResolutionWidth();
            int width = config.getVideoCaptureResolutionHeight();
            config.setVideoEncodeResolution(width, height);
            config.setVideoCaptureResolution(width, height);
            mZegoLiveRoom.setAVConfig(config);
        }

        // 设置水印
        ZegoLiveRoom.setWaterMarkImagePath("asset:watermark.png");
        Rect rect = new Rect();
        rect.left = 30;
        rect.top = 10;
        rect.right = 180;
        rect.bottom = 160;
        ZegoLiveRoom.setPreviewWaterMarkRect(rect);

        mZegoLiveRoom.enableMic(true);
        mZegoLiveRoom.enableCamera(true);

        textureView.setVisibility(View.VISIBLE);

        mZegoLiveRoom.setPreviewView(textureView);

        mZegoLiveRoom.startPreview();
        mZegoLiveRoom.setPreviewViewMode(ZegoVideoViewMode.ScaleAspectFill);
        mZegoLiveRoom.setFrontCam(tbEnableFrontCam.isChecked());
        mZegoLiveRoom.enableTorch(tbEnableTorch.isChecked());
        // 设置美颜
        mZegoLiveRoom.enableBeautifying(ZegoRoomUtil.getZegoBeauty(mSelectedBeauty));
        // 设置滤镜
        mZegoLiveRoom.setFilter(mSelectedFilter);

    }

    private void stopPreview() {
        textureView.setVisibility(View.INVISIBLE);
        mZegoLiveRoom.stopPreview();
        mZegoLiveRoom.setPreviewView(null);

    }


    public void refresh() {
        stopPreview();
        ZegoApiManager.getInstance().releaseSDK();
        long newAppId = PreferenceUtil.getInstance().getAppId();
        byte[] newSignKey = PreferenceUtil.getInstance().getAppKey();
        ZegoApiManager.getInstance().reInitSDK(newAppId, newSignKey);
        initPreview();
    }

    /**
     * @see MainActivity.OnReInitSDKCallback#onReInitSDK()
     */
    @Override
    public void onReInitSDK() {
        if (!mIsVisibleToUser) return;

        // 6.0及以上的系统需要在运行时申请CAMERA RECORD_AUDIO权限
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(mParentActivity, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED
                    || ContextCompat.checkSelfPermission(mParentActivity, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(mParentActivity, new String[]{
                        Manifest.permission.CAMERA, Manifest.permission.RECORD_AUDIO}, 101);
            } else {
                initPreview();
            }
        } else {

            refresh();

        }
    }
}
