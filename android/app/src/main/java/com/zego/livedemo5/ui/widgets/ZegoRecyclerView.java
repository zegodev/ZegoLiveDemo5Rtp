package com.zego.livedemo5.ui.widgets;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.util.AttributeSet;
import android.view.MotionEvent;


/**
 * Created by zego on 2018/11/9.
 */

public class ZegoRecyclerView extends RecyclerView {


    public ZegoRecyclerView(Context context) {
        super(context);
    }

    public ZegoRecyclerView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public ZegoRecyclerView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {


        return false;
    }

}
