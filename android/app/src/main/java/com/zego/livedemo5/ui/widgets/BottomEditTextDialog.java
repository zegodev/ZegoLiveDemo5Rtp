package com.zego.livedemo5.ui.widgets;

import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Point;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewTreeObserver;
import android.view.Window;
import android.view.WindowManager;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.zego.livedemo5.R;

/**
 * Created by zego on 2019/3/28.
 */

public class BottomEditTextDialog extends Dialog implements View.OnLayoutChangeListener {

    private boolean isCancelable;//控制点击dialog外部是否dismiss
    private boolean isBackCancelable;//控制返回键是否dismiss
    private Context context;
    private String msg;

    //屏幕高度
    private int screenHeight = 0;
    //软件盘弹起后所占高度阀值
    private int keyHeight = 0;

    public BottomEditTextDialog(String msg, Context context, boolean isCancelable, boolean isBackCancelable) {
        super(context, R.style.MyDialog);
        this.context = context;
        this.msg = msg;
        this.isCancelable = isCancelable;
        this.isBackCancelable = isBackCancelable;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        WindowManager wmManager = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        Point size = new Point();
        wmManager.getDefaultDisplay().getSize(size);
        //获取屏幕高度
        screenHeight = size.y;
        //阀值设置为屏幕高度的1/3
        keyHeight = screenHeight / 3;
        setContentView(R.layout.dialog_editext);//这行一定要写在前面
        setCancelable(isCancelable);//点击外部不可dismiss
        setCanceledOnTouchOutside(isBackCancelable);
        Window window = this.getWindow();
        window.setGravity(Gravity.BOTTOM);
        WindowManager.LayoutParams params = window.getAttributes();
        params.width = WindowManager.LayoutParams.MATCH_PARENT;
        params.height = WindowManager.LayoutParams.MATCH_PARENT;
        window.setAttributes(params);
        editText = findViewById(R.id.edit_text);
        editText.setText(msg);
        editText.addOnLayoutChangeListener(this);
        findViewById(R.id.dialog).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BottomEditTextDialog.this.cancel();
            }
        });

    }

    @Override
    public void cancel() {
        editText.removeOnLayoutChangeListener(this);
        super.cancel();
        context = null;
    }

    EditText editText;

    @Override
    public void show() {
        super.show();

        if (editText != null) {
            getWindow().clearFlags(WindowManager.LayoutParams.FLAG_ALT_FOCUSABLE_IM);
            //弹出对话框后直接弹出键盘
            editText.setFocusableInTouchMode(true);
            editText.requestFocus();
            editText.postDelayed(new Runnable() {
                @Override
                public void run() {
                    InputMethodManager inputManager = (InputMethodManager) editText.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                    inputManager.showSoftInput(editText, 0);
                }
            }, 200);
        }
    }

    @Override
    public void onLayoutChange(View v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom) {
        if (oldBottom != 0 && bottom != 0 && (bottom - oldBottom > keyHeight)) {
            BottomEditTextDialog.this.cancel();
        }

    }

    public String getMsg() {
        if (editText != null) {
            return editText.getText().toString();
        } else {
            return "";
        }
    }
}
