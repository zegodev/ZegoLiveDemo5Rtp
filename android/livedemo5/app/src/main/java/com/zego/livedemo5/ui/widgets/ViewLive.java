package com.zego.livedemo5.ui.widgets;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.content.res.TypedArray;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.view.WindowManager;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.zego.livedemo5.R;
import com.zego.livedemo5.ui.activities.moreanchors.MoreAnchorsPublishActivity;
import com.zego.livedemo5.utils.ShareUtils;
import com.zego.zegoliveroom.ZegoLiveRoom;
import com.zego.zegoliveroom.constants.ZegoVideoViewMode;

import java.util.ArrayList;
import java.util.List;


/**
 * Copyright © 2017 Zego. All rights reserved.
 * des: 直播view.
 */
public class ViewLive extends RelativeLayout {

    /**
     * 推拉流颜色.
     */
    private TextView mTvQualityColor;

    /**
     * 推拉流质量.
     */
    private TextView mTvQuality;

    /**
     * 全屏.
     */
    private TextView mTvSwitchToFullScreen;

    /**
     * 分享.
     */
    private TextView mTvShare;

    /**
     * 用于渲染视频.
     */
    private TextureView mTextureView;

    private int[] mArrColor;

    private String[] mArrLiveQuality;

    private Resources mResources;

    private View mRootView;

    private ZegoLiveRoom mZegoLiveRoom = null;

    private Activity mActivityHost = null;

    /**
     * 推拉流质量.
     */
    private int mLiveQuality = 0;

    /**
     * 视频显示模式.
     */
    private int mZegoVideoViewMode = ZegoVideoViewMode.ScaleAspectFit;

    /**
     * 分享地址.
     */
    private List<String> mListShareUrls = new ArrayList<>();

    /**
     * "切换全屏" 标记.
     */
    private boolean mNeedToSwitchFullScreen = false;

    private String mStreamID = null;

    private boolean mIsPublishView = false;

    private boolean mIsPlayView = false;

    private IShareToQQCallback mShareToQQCallback = null;


    public ViewLive(Context context) {
        super(context);
    }

    public ViewLive(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public ViewLive(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);

        TypedArray a = context.obtainStyledAttributes(attrs, R.styleable.ViewLive, defStyleAttr, 0);
        boolean isBigView = a.getBoolean(R.styleable.ViewLive_isBigView, false);
        a.recycle();

        initViews(context, isBigView);
    }

    public void setZegoLiveRoom(ZegoLiveRoom zegoLiveRoom) {
        mZegoLiveRoom = zegoLiveRoom;
    }

    public void setActivityHost(Activity activity) {
        mActivityHost = activity;
    }

    public void destroy() {
        mActivityHost = null;
        mShareToQQCallback = null;
        mZegoLiveRoom = null;
        if (mTvSwitchToFullScreen != null) {
            mTvSwitchToFullScreen.setOnClickListener(null);
        }
    }

    public void setShareToQQCallback(IShareToQQCallback shareToQQCallback) {
        mShareToQQCallback = shareToQQCallback;
    }

    private void initViews(Context context, boolean isBigView) {

        mResources = context.getResources();

        mArrColor = new int[4];
        mArrColor[0] = R.drawable.circle_green;
        mArrColor[1] = R.drawable.circle_yellow;
        mArrColor[2] = R.drawable.circle_red;
        mArrColor[3] = R.drawable.circle_gray;

        mArrLiveQuality = mResources.getStringArray(R.array.live_quality);

        if (isBigView) {
            mRootView = LayoutInflater.from(context).inflate(R.layout.view_live_big, this);

            mTvSwitchToFullScreen = (TextView) mRootView.findViewById(R.id.tv_switch_full_screen);
            mTvSwitchToFullScreen.setOnClickListener(new OnClickListener() {
                @Override
                public void onClick(View v) {

                    if (mZegoVideoViewMode == ZegoVideoViewMode.ScaleAspectFill) {
                        setZegoVideoViewMode(mNeedToSwitchFullScreen, ZegoVideoViewMode.ScaleAspectFit);
                    } else if (mZegoVideoViewMode == ZegoVideoViewMode.ScaleAspectFit) {
                        setZegoVideoViewMode(mNeedToSwitchFullScreen, ZegoVideoViewMode.ScaleAspectFill);
                    }

                    if (mIsPlayView && mZegoLiveRoom != null && mActivityHost != null) {

                        mZegoLiveRoom.setViewMode(mZegoVideoViewMode, mStreamID);
                        WindowManager wm = (WindowManager) mActivityHost.getSystemService(Context.WINDOW_SERVICE);
                        int currentOrientation = wm.getDefaultDisplay().getRotation();
                        if (mZegoVideoViewMode == ZegoVideoViewMode.ScaleAspectFit) {
                            if (currentOrientation == Surface.ROTATION_90 || currentOrientation == Surface.ROTATION_270) {
                                mZegoLiveRoom.setViewRotation(Surface.ROTATION_90, mStreamID);
                            } else {
                                mZegoLiveRoom.setViewRotation(Surface.ROTATION_0, mStreamID);
                            }
                        } else if (mZegoVideoViewMode == ZegoVideoViewMode.ScaleAspectFill) {
                            if (currentOrientation == Surface.ROTATION_90 || currentOrientation == Surface.ROTATION_270) {
                                mZegoLiveRoom.setViewRotation(Surface.ROTATION_0, mStreamID);
                            } else {
                                mZegoLiveRoom.setViewRotation(Surface.ROTATION_90, mStreamID);
                            }

                        }
                    }
                }
            });

            mTvShare = (TextView) mRootView.findViewById(R.id.tv_share);
            mTvShare.setOnClickListener(new OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (mActivityHost != null && mShareToQQCallback != null) {
                        ShareUtils.getInstance().shareToQQ(mActivityHost, mListShareUrls, mShareToQQCallback.getRoomID(), mStreamID);
                    }
                }
            });
        } else {
            mRootView = LayoutInflater.from(context).inflate(R.layout.view_live, this);
        }

        mTextureView = (TextureView) mRootView.findViewById(R.id.textureView);
        mTvQualityColor = (TextView) mRootView.findViewById(R.id.tv_quality_color);
        mTvQuality = (TextView) mRootView.findViewById(R.id.tv_live_quality);
    }

    /**
     * 返回view是否为"空闲"状态.
     */
    public boolean isFree() {
        return TextUtils.isEmpty(mStreamID);
    }

    /**
     * 释放view.
     */
    public void setFree() {
        mLiveQuality = 0;
        setVisibility(View.INVISIBLE);

        mZegoVideoViewMode = ZegoVideoViewMode.ScaleAspectFill;
        mNeedToSwitchFullScreen = false;

        if (mTvSwitchToFullScreen != null) {
            mTvSwitchToFullScreen.setVisibility(View.INVISIBLE);
        }

        mListShareUrls = new ArrayList<>();
        if (mTvShare != null) {
            mTvShare.setVisibility(View.INVISIBLE);
        }

        mStreamID = null;
        mIsPublishView = false;
        mIsPlayView = false;
    }


    /**
     * 交换view, 通常是跟大的View交换.
     */
    public void toExchangeView(ViewLive vlBigView) {
        // 交换view
        if (vlBigView.isPublishView()) {
            if (mZegoLiveRoom != null) {
                String streamID = vlBigView.getStreamID();
                if (!TextUtils.isEmpty(streamID) && streamID.startsWith(MoreAnchorsPublishActivity.TAG_AUX)) {
                    mZegoLiveRoom.setPreviewView(mTextureView, MoreAnchorsPublishActivity.AUX_CHANNEL_INDEX);
                } else {
                    mZegoLiveRoom.setPreviewView(mTextureView);
                }
            }
        } else if (vlBigView.isPlayView()) {
            if (mZegoLiveRoom != null) {
                mZegoLiveRoom.updatePlayView(vlBigView.getStreamID(), mTextureView);
            }
        }

        // 交换view
        if (isPublishView()) {
            if (mZegoLiveRoom != null) {
                if (!TextUtils.isEmpty(mStreamID) && mStreamID.startsWith(MoreAnchorsPublishActivity.TAG_AUX)) {
                    mZegoLiveRoom.setPreviewView(vlBigView.getTextureView(), MoreAnchorsPublishActivity.AUX_CHANNEL_INDEX);
                } else {
                    mZegoLiveRoom.setPreviewView(vlBigView.getTextureView());
                }
            }
        } else if (isPlayView()) {
            if (mZegoLiveRoom != null) {
                mZegoLiveRoom.updatePlayView(mStreamID, vlBigView.getTextureView());
            }
        }

        // 交换流信息
        String streamIDTemp = mStreamID;
        mStreamID = vlBigView.getStreamID();
        vlBigView.setStreamID(streamIDTemp);

        boolean isPublishViewTemp = mIsPublishView;
        mIsPublishView = vlBigView.isPublishView();
        vlBigView.setPublishView(isPublishViewTemp);

        boolean isPlayViewTemp = mIsPlayView;
        mIsPlayView = vlBigView.isPlayView();
        vlBigView.setPlayView(isPlayViewTemp);

        // 交换quality
        int liveQualityOfBigView = vlBigView.getLiveQuality();
        int liveQualityOfSmallView = mLiveQuality;
        vlBigView.setLiveQuality(liveQualityOfSmallView);
        setLiveQuality(liveQualityOfBigView);

        // 交换"全屏播放"的标记, 交换view mode
        boolean needToSwitchFullScreenOfBigView = vlBigView.isNeedToSwitchFullScreen();
        boolean needToSwitchFullScreenOfSmallView = mNeedToSwitchFullScreen;
        int modeOfBigView = vlBigView.getZegoVideoViewMode();
        int modeOfSmallView = mZegoVideoViewMode;
        vlBigView.setZegoVideoViewMode(needToSwitchFullScreenOfSmallView, modeOfSmallView);
        setZegoVideoViewMode(needToSwitchFullScreenOfBigView, modeOfBigView);

        // 交换share urls
        List<String> listShareUrlsOfBifView = vlBigView.getListShareUrls();
        List<String> listShareUrlsOfSmallView = mListShareUrls;
        vlBigView.setListShareUrls(listShareUrlsOfSmallView);

        setListShareUrls(listShareUrlsOfBifView);
    }

    /**
     * 设置播放质量.
     */
    public void setLiveQuality(int quality) {
        if (quality >= 0 && quality <= 3) {
            mLiveQuality = quality;
            mTvQualityColor.setBackgroundResource(mArrColor[quality]);
            mTvQuality.setText(mResources.getString(R.string.live_quality, mArrLiveQuality[quality]));
        }
    }

    public void setLiveQuality(int quality, double videoFPS, double videoBitrates) {
        setLiveQuality(quality);
        mTvQuality.append(mResources.getString(R.string.live_quality_fps_and_bitrate, videoFPS, videoBitrates));
    }


    /**
     * 设置mode.
     */
    public void setZegoVideoViewMode(boolean needToSwitchFullScreen, int mode) {
        mNeedToSwitchFullScreen = needToSwitchFullScreen;
        mZegoVideoViewMode = mode;

        if (mTvSwitchToFullScreen != null) {
            if (mNeedToSwitchFullScreen) {
                // mTvSwitchToFullScreen.setVisibility(View.VISIBLE);

                if (mode == ZegoVideoViewMode.ScaleAspectFill) {
                    // 退出全屏
                    mTvSwitchToFullScreen.setText(R.string.exit_full_screen);
                } else if (mode == ZegoVideoViewMode.ScaleAspectFit) {
                    // 全屏显示
                    mTvSwitchToFullScreen.setText(R.string.full_screen);
                }
            } else {
                mTvSwitchToFullScreen.setVisibility(View.INVISIBLE);
            }
        }
    }

    /**
     * 设置分享url列表.
     */
    public void setListShareUrls(List<String> listShareUrls) {
        mListShareUrls.clear();
        mListShareUrls.addAll(listShareUrls);

        if (mTvShare != null) {
            if (listShareUrls.size() > 0) {
                mTvShare.setVisibility(View.VISIBLE);
            } else {
                mTvShare.setVisibility(View.INVISIBLE);
            }
        }
    }


    public int getLiveQuality() {
        return mLiveQuality;
    }

    public TextureView getTextureView() {
        return mTextureView;
    }

    public boolean isNeedToSwitchFullScreen() {
        return mNeedToSwitchFullScreen;
    }


    public int getZegoVideoViewMode() {
        return mZegoVideoViewMode;
    }


    public List<String> getListShareUrls() {
        return mListShareUrls;
    }

    public void setStreamID(String streamID) {
        mStreamID = streamID;
    }

    public String getStreamID() {
        return mStreamID;
    }

    public boolean isPublishView() {
        return mIsPublishView;
    }

    public boolean isPlayView() {
        return mIsPlayView;
    }

    public void setPublishView(boolean publishView) {
        mIsPublishView = publishView;
    }

    public void setPlayView(boolean playView) {
        mIsPlayView = playView;
    }

    public interface IShareToQQCallback {
        String getRoomID();
    }
}
