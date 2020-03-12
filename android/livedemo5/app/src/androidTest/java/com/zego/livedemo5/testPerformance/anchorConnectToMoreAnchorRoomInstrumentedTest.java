package com.zego.livedemo5.testPerformance;

import android.app.Activity;
import android.support.test.InstrumentationRegistry;
import android.support.test.filters.LargeTest;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;
import android.support.test.uiautomator.UiDevice;
import android.support.test.uiautomator.UiObject;
import android.support.test.uiautomator.UiObjectNotFoundException;
import android.support.test.uiautomator.UiSelector;

import com.zego.livedemo5.MainActivity;
import com.zego.livedemo5.R;

import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static android.support.test.espresso.matcher.ViewMatchers.withText;
import static com.zego.livedemo5.tools.CommonTools.printLog;
import static com.zego.livedemo5.tools.CommonTools.sleep;
import static com.zego.livedemo5.tools.PermissionTool.clickToGetPermission;

/**
 * Created by cier on 2017/6/2.
 */
@RunWith(AndroidJUnit4.class)
@LargeTest
public class anchorConnectToMoreAnchorRoomInstrumentedTest {
    private Activity mActivity;

    @Rule
    public ActivityTestRule<MainActivity> mMainActicity=new ActivityTestRule<MainActivity>(MainActivity.class);

    @BeforeClass
    public static void init(){
        printLog("anchorConnectToMoreAnchorRoomInstrumentedTest->init()");
    }

    @AfterClass
    public static void unInit(){
        printLog("anchorConnectToMoreAnchorRoomInstrumentedTest->uInit()");
    }

    @Before
    public void setup(){
        printLog("anchorConnectToMoreAnchorRoomInstrumentedTest->setup()");
        mActivity=mMainActicity.getActivity();
    }

    @Test
    public void testStart(){
        joinToMoreAnchor(PerformanceTest.RUNTIME);
    }

    public void joinToMoreAnchor(int minute){
        sleep(30000);
        onView(withText(anchorStartMoreAnchorInstrumentedTest.moreAnchorRoomName)).perform(click());//点击房间进入
        sleep(2000);
        onView(withId(R.id.tv_speaker)).perform(click());
        sleep(10000);
        onView(withId(R.id.tv_publish_control)).perform(click());
//        GetPermission(20);
        sleep(60*1000*minute);
        endPublish();
    }

    public void endPublish(){
        onView(withId(R.id.tv_close)).perform(click());
        sleep(500);
        onView(withText(R.string.Yes)).perform(click());
    }

    public static void GetPermission(int waitTime){
        sleep(1000);
        UiDevice uiDevice=UiDevice.getInstance(InstrumentationRegistry.getInstrumentation());
        UiObject button=uiDevice.findObject(new UiSelector().className("android.widget.Button").text("允许"));

        if(button.waitForExists(waitTime*1000)){
            try {
                button.click();
                GetPermission(waitTime);
            } catch (UiObjectNotFoundException e) {
                e.printStackTrace();
            }
        }
    }
}
