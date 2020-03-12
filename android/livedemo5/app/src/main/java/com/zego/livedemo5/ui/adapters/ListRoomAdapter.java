package com.zego.livedemo5.ui.adapters;

import android.content.Context;
import android.content.res.Resources;
import android.support.v7.widget.RecyclerView;
import android.text.TextUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.zego.livedemo5.R;
import com.zego.support.RoomInfo;
import com.zego.livedemo5.ui.widgets.CirImageView;
import com.zego.livedemo5.ui.widgets.MaterialProgressBarSupport;

import java.util.List;

/**
 * Copyright © 2016 Zego. All rights reserved.
 *
 * des:  直播列表适配器.
 */
public class ListRoomAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {

    public static final int TYPE_FOOTER = Integer.MIN_VALUE;
    public static final int TYPE_ITEM = 0;
    private boolean hasMoreData = true;

    private LayoutInflater mLayoutInflater;
    private List<RoomInfo> mListRoom;
    private OnItemClickListener mOnItemClickListener;
    private Resources mResources;

    public void setOnItemClickListener(OnItemClickListener onItemClickListener) {
        mOnItemClickListener = onItemClickListener;
    }

    public ListRoomAdapter(Context context, List<RoomInfo> listRoom) {
        mListRoom = listRoom;
        mLayoutInflater = LayoutInflater.from(context);
        mResources = context.getResources();
    }

    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        if (viewType == TYPE_FOOTER) {
            return new FooterViewHolder(mLayoutInflater.inflate(R.layout.view_list_footer, parent, false));
        } else {
            return new LiveListHolder(mLayoutInflater.inflate(R.layout.item_room, parent, false));
        }
    }

    @Override
    public void onBindViewHolder(final RecyclerView.ViewHolder holder, int position) {
        if (holder instanceof FooterViewHolder) {
            if (hasMoreData) {
                ((FooterViewHolder) holder).mProgressView.setVisibility(View.VISIBLE);
                ((FooterViewHolder) holder).mProgressView.startProgress();

                ((FooterViewHolder) holder).mTextView.setText(R.string.app_loading_more);
            } else {
                ((FooterViewHolder) holder).mProgressView.stopProgress();
                ((FooterViewHolder) holder).mProgressView.setVisibility(View.GONE);
                ((FooterViewHolder) holder).mTextView.setText(R.string.app_no_more_data);
                ((FooterViewHolder) holder).mTextView.setVisibility(View.GONE);
            }
        } else {
            RoomInfo room = mListRoom.get(position);
            String roomName = room.getRoomName();
            if(TextUtils.isEmpty(roomName)){
                roomName = room.getRoomId();
            }
            ((LiveListHolder) holder).tvPulishTitle.setText(roomName);
            ((LiveListHolder) holder).tvPublishTime.setText(room.getAnchorNickName());

            if (mOnItemClickListener != null) {
                ((LiveListHolder) holder).rlytItem.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        mOnItemClickListener.OnItemClick(((LiveListHolder) holder).rlytItem, holder.getLayoutPosition());
                    }
                });
            }
        }
    }

    @Override
    public int getItemViewType(int position) {
        if (position == mListRoom.size()) {
            return TYPE_FOOTER;
        }
        return TYPE_ITEM;
    }

    @Override
    public int getItemCount() {
        if (mListRoom == null || mListRoom.size() == 0) {
            return 0;
        }
        return mListRoom.size() + 1;
    }


    public class LiveListHolder extends RecyclerView.ViewHolder {
        RelativeLayout rlytItem;
        CirImageView civAvatar;
        TextView tvPulishTitle;
        TextView tvPublishTime;
        TextView tvLiveCount;

        public LiveListHolder(View itemView) {
            super(itemView);
            rlytItem = (RelativeLayout) itemView.findViewById(R.id.rlyt_item);
            civAvatar = (CirImageView) itemView.findViewById(R.id.civ_avatar);
            tvPulishTitle = (TextView) itemView.findViewById(R.id.tv_publish_title);
            tvPublishTime = (TextView) itemView.findViewById(R.id.tv_publish_time);
            tvLiveCount = (TextView) itemView.findViewById(R.id.tv_live_count);
        }
    }

    public class FooterViewHolder extends RecyclerView.ViewHolder {
        public final MaterialProgressBarSupport mProgressView;
        public final TextView mTextView;

        public FooterViewHolder(View view) {
            super(view);
            mProgressView = (MaterialProgressBarSupport) view.findViewById(R.id.progress_view);
            mTextView = (TextView) view.findViewById(R.id.tv_content);
        }

        @Override
        public String toString() {
            return super.toString() + " '" + mTextView.getText();
        }
    }

    public interface OnItemClickListener {
        void OnItemClick(View view, int position);
    }

    public void setHasMoreData(boolean hasMoreData) {
        if (this.hasMoreData != hasMoreData) {
            this.hasMoreData = hasMoreData;
            notifyDataSetChanged();
        }
    }
}
