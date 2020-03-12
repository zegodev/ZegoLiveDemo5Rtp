package com.zego.livedemo5.tools;

import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.uiautomator.UiDevice;
import android.support.test.uiautomator.UiObject;
import android.support.test.uiautomator.UiObjectNotFoundException;
import android.support.test.uiautomator.UiSelector;

import com.zego.livedemo5.R;

import static com.zego.livedemo5.tools.CommonTools.printLog;

/**
 * Created by realuei on 2017/3/22.
 */

public class JoinLiveRequestMonitor extends Thread {

    public JoinLiveRequestMonitor(String name) {
        super(name);
    }

    @Override
    public void run() {
        Context context = InstrumentationRegistry.getTargetContext();
        UiDevice uiDevice = UiDevice.getInstance(InstrumentationRegistry.getInstrumentation());
        UiObject uiObject = uiDevice.findObject(new UiSelector().className("android.widget.Button").resourceId("android:id/button1").text(context.getString(R.string.Allow)));
        while (!isInterrupted()) {
            if (uiObject.waitForExists(2 * 1000)) {
                try {
                    uiObject.click();
                } catch (UiObjectNotFoundException e) {
                    printLog("when wait join live request exception: %s", e);
                }
            }
        }
    }

    @Override
    public void interrupt() {
        super.interrupt();

        // wait for run finish
        CommonTools.sleep(2000);
    }

}
