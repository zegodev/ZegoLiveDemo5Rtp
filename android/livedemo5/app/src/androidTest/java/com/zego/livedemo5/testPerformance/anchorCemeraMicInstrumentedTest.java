package com.zego.livedemo5.testPerformance;

import android.app.Activity;
import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.filters.LargeTest;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;
import android.support.test.uiautomator.UiDevice;
import android.support.test.uiautomator.UiObject;
import android.support.test.uiautomator.UiSelector;

import com.zego.livedemo5.MainActivity;
import com.zego.livedemo5.R;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;
import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.clearText;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.action.ViewActions.closeSoftKeyboard;
import static android.support.test.espresso.action.ViewActions.replaceText;
import static android.support.test.espresso.action.ViewActions.typeText;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static android.support.test.espresso.matcher.ViewMatchers.withText;
import static com.zego.livedemo5.PublishInstrumentedTest.waitForPublishSuccess;
import static com.zego.livedemo5.tools.CommonTools.printLog;
import static com.zego.livedemo5.tools.CommonTools.sleep;
import static com.zego.livedemo5.tools.PermissionTool.allowPermissionIfNeed;
import static com.zego.livedemo5.tools.PermissionTool.clickToGetPermission;

/**
 * Created by cier on 2017/6/2.
 */
@RunWith(AndroidJUnit4.class)
@LargeTest
public class anchorCemeraMicInstrumentedTest {
    private Activity mActivity;

    @Rule
    public ActivityTestRule<MainActivity> mActivityRule=new ActivityTestRule<MainActivity>(MainActivity.class);

    @Before
    public void setup(){
        mActivity=mActivityRule.getActivity();
        onView(withText(mActivity.getResources().getStringArray(R.array.navigation_bar_titles)[1])).perform(click());
        sleep(PerformanceTest.WAITTIMEBEFOREPUBLISH);
//        clickToGetPermission(5);
//        allowPermissionIfNeed();
    }

    @Test
    public void startTest(){
        test1(PerformanceTest.RUNTIME+2);
    }

    /**
     * 开启摄像头+麦克风
     * @param minute
     */
    public void test1(int minute){
        printLog("onlyOpenCamaraAndMicTest");
        sleep(1000);
        startPublish(anchorCameraInstrumentedTest.roomName,R.id.tv_select_single_anchor);
        sleep(2000);
        onView(withId(R.id.tv_speaker)).perform(click());
        sleep(60*1000*minute);
        endPublish();
    }

    public void startPublish(String publishName,int publishType){
        //设置房间名
        onView(withId(R.id.et_publish_title)).perform(clearText(),replaceText(publishName));
        sleep(500);
        //点击开始按钮
        onView(withId(R.id.btn_start_publish)).perform(click());
        sleep(500);
        //选择主播类型
        onView(withId(publishType)).perform(click());
    }

    public void endPublish(){
        onView(withId(R.id.tv_close)).perform(click());
        sleep(500);
        onView(withText(R.string.Yes)).perform(click());
    }
}
