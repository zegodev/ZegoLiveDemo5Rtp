package com.zego.livedemo5.ui.adapters;

import android.content.Context;
import android.content.res.Resources;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.zego.livedemo5.R;
import com.zego.livedemo5.entities.ZegoStream;

import java.util.List;

/**
 * Copyright © 2017 Zego. All rights reserved.
 */
public class LiveViewsAdapter extends RecyclerView.Adapter<LiveViewsAdapter.LiveViewHolder> {

    private List<ZegoStream> mListStream = null;
    private LayoutInflater mLayoutInflater = null;
    private Resources mResources = null;
    private int[] mArrQualityColor = null;
    private String[] mArrQualityText = null;
    private OnVideoLiveCallback mVideoLiveCallback = null;

    public LiveViewsAdapter(Context context) {
        mLayoutInflater = LayoutInflater.from(context);
        mResources = context.getResources();

        mArrQualityColor = new int[4];
        mArrQualityColor[0] = R.drawable.circle_green;
        mArrQualityColor[1] = R.drawable.circle_yellow;
        mArrQualityColor[2] = R.drawable.circle_red;
        mArrQualityColor[3] = R.drawable.circle_gray;

        mArrQualityText = mResources.getStringArray(R.array.live_quality);
    }

    @Override
    public LiveViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        return new LiveViewHolder(mLayoutInflater.inflate(R.layout.item_live_view, parent, false));
    }

    @Override
    public void onBindViewHolder(LiveViewHolder holder, int position) {
        ZegoStream zegoStream = mListStream.get(position);

        int liveQuality = zegoStream.getLiveQuality();
        if (liveQuality >= 0 && liveQuality <= 3) {
            holder.tvQualityColor.setBackgroundResource(mArrQualityColor[liveQuality]);
            holder.tvQuality.setText(mResources.getString(R.string.live_quality, mArrQualityText[liveQuality]));
        }

        if (mVideoLiveCallback != null) {
            if (zegoStream.getStreamType() == ZegoStream.StreamType.Publish) {

                mVideoLiveCallback.onStartPublish(zegoStream.getStreamID(), holder.textureView, zegoStream.getZegoVideoViewMode());

            } else if (zegoStream.getStreamType() == ZegoStream.StreamType.Play) {

                mVideoLiveCallback.onStartPlay(zegoStream.getStreamID(), holder.textureView, zegoStream.getZegoVideoViewMode());

            }
        }
    }

    @Override
    public int getItemCount() {
        return mListStream == null ? 0 : mListStream.size();
    }

    public void setVideoLiveCallback(OnVideoLiveCallback callback) {
        mVideoLiveCallback = callback;
    }

    public static class LiveViewHolder extends RecyclerView.ViewHolder {

        TextureView textureView;

        TextView tvQualityColor;

        TextView tvQuality;

        public LiveViewHolder(View itemView) {
            super(itemView);

            textureView = (TextureView) itemView.findViewById(R.id.textureView);
            tvQualityColor = (TextView) itemView.findViewById(R.id.tv_quality_color);
            tvQuality = (TextView) itemView.findViewById(R.id.tv_live_quality);
        }
    }

    public interface OnVideoLiveCallback {
        void onStartPublish(String streamID, TextureView textureView, int zegoLiveMode);

        void onStartPlay(String streamID, TextureView textureView, int zegoLiveMode);
    }
}
