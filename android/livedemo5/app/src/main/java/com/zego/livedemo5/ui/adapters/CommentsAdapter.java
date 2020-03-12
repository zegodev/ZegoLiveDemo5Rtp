package com.zego.livedemo5.ui.adapters;

import android.content.Context;
import android.graphics.Color;
import android.support.v7.widget.RecyclerView;
import android.text.Spannable;
import android.text.SpannableStringBuilder;
import android.text.style.ForegroundColorSpan;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import com.zego.livedemo5.R;
import com.zego.zegoliveroom.entity.ZegoRoomMessage;

import java.util.List;

/**
 * Copyright © 2017 Zego. All rights reserved.
 */

public class CommentsAdapter extends RecyclerView.Adapter {

    private List<ZegoRoomMessage> mListMsg;

    private LayoutInflater mInflater;

    public CommentsAdapter(Context context, List<ZegoRoomMessage> list) {
        mInflater = LayoutInflater.from(context);
        mListMsg = list;
    }


    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_user_comment, parent, false);
        final MyViewHolder myViewHolder = new MyViewHolder(v);
        return myViewHolder;
    }

    @Override
    public void onBindViewHolder(final RecyclerView.ViewHolder holder, int position) {

        final MyViewHolder myViewHolder = (MyViewHolder) holder;
        ZegoRoomMessage msg = mListMsg.get(position);
        myViewHolder.msgContent.setText(getStringBuilder(msg.fromUserName, msg.content));
    }

    @Override
    public long getItemId(int i) {
        return 0;
    }

    @Override
    public int getItemCount() {
        return mListMsg == null ? 0 : mListMsg.size();
    }

    public void addMsgList(List<ZegoRoomMessage> listMsg) {
        mListMsg.addAll(listMsg);
        notifyDataSetChanged();
    }

    public void addMsg(ZegoRoomMessage msg) {
        if (msg != null) {
            mListMsg.add(msg);
            notifyDataSetChanged();
        }
    }


    public static class MyViewHolder extends RecyclerView.ViewHolder {
        TextView msgContent;

        public MyViewHolder(View itemView) {
            super(itemView);
            msgContent = (TextView) itemView.findViewById(R.id.tv_msg_content);

        }
    }

    private SpannableStringBuilder getStringBuilder(String fromUserName, String content) {
        fromUserName = fromUserName.trim() + ":";
        content = content.trim();
        SpannableStringBuilder builder = new SpannableStringBuilder(fromUserName + content);

        //ForegroundColorSpan 为文字前景色，BackgroundColorSpan为文字背景色
        ForegroundColorSpan whiteSpan = new ForegroundColorSpan(Color.WHITE);
        ForegroundColorSpan yellowSpan = new ForegroundColorSpan(Color.YELLOW);

        builder.setSpan(yellowSpan, 0, fromUserName.length() - 1, Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);
        builder.setSpan(whiteSpan, fromUserName.length(), fromUserName.length() + content.length(), Spannable.SPAN_INCLUSIVE_INCLUSIVE);

        return builder;
    }

    public List<ZegoRoomMessage> getListMsg() {
        return mListMsg;
    }
}
