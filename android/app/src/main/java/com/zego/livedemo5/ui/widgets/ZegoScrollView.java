package com.zego.livedemo5.ui.widgets;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.widget.ScrollView;

/**
 * Created by zego on 2019/1/9.
 */

public class ZegoScrollView extends ScrollView {
    public ZegoScrollView(Context context) {
        this(context, null);
    }

    public ZegoScrollView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public ZegoScrollView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @Override
    public boolean onTouchEvent(MotionEvent ev) {
        switch (ev.getAction()) {
            case MotionEvent.ACTION_DOWN:
                return false;
            default:
                return super.onTouchEvent(ev);
        }
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent ev) {
        return false;
    }
}
