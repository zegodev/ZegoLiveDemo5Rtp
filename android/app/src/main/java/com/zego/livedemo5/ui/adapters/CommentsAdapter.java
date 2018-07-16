package com.zego.livedemo5.ui.adapters;

import android.content.Context;
import android.graphics.Color;
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

public class CommentsAdapter extends BaseAdapter {

    private List<ZegoRoomMessage> mListMsg;

    private LayoutInflater mInflater;

    public CommentsAdapter(Context context, List<ZegoRoomMessage> list) {
        mInflater = LayoutInflater.from(context);
        mListMsg = list;
    }

    @Override
    public int getCount() {
        return mListMsg == null ? 0 : mListMsg.size();
    }

    @Override
    public Object getItem(int i) {
        return null;
    }

    @Override
    public long getItemId(int i) {
        return 0;
    }

    public void addMsgList(List<ZegoRoomMessage> listMsg){
        mListMsg.addAll(listMsg);
        notifyDataSetChanged();
    }

    public void addMsg(ZegoRoomMessage msg){
        if(msg != null){
            mListMsg.add(msg);
            notifyDataSetChanged();
        }
    }

    @Override
    public View getView(int position, View convertView, ViewGroup viewGroup) {
        ViewHolder holder;

        if (convertView == null) {
            holder = new ViewHolder();

            convertView = mInflater.inflate(R.layout.item_user_comment, null);
            holder.msgContent = (TextView) convertView.findViewById(R.id.tv_msg_content);
            convertView.setTag(holder);
        } else {
            holder = (ViewHolder) convertView.getTag();
        }

        ZegoRoomMessage msg = mListMsg.get(position);
        holder.msgContent.setText(getStringBuilder(msg.fromUserName, msg.content));

        return convertView;
    }

    final class ViewHolder {
        TextView msgContent;
    }

    private SpannableStringBuilder getStringBuilder(String fromUserName, String content){
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
