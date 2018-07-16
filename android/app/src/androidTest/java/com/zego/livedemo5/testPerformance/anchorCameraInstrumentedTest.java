package com.zego.livedemo5.testPerformance;

import android.app.Activity;
import android.support.test.filters.LargeTest;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

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
public class anchorCameraInstrumentedTest {
    private Activity mActivity;

    public static final String roomName="000testSingleRoomPublish";

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
        test3(PerformanceTest.RUNTIME+2);
    }

    /**
     * 仅开启摄像头
     * @param minute
     */
    public void test3(int minute){
        printLog("onlyOpenCameraTest");
        sleep(1000);
        startPublish(roomName,R.id.tv_select_single_anchor);
        sleep(2000);
        onView(withId(R.id.tv_speaker)).perform(click());
        openOrCloseMicrophone();
        sleep(60*1000*minute);
        endPublish();
    }

    /**
     * 麦克风默认是打开的
     */
    public void openOrCloseMicrophone(){
//        waitForPublishSuccess(5000, mActivity);//点击设置之前要等待推流成功
        sleep(30000);//暂停30s等待推流结束
        onView(withId(R.id.tv_publish_settings)).perform(click());
        sleep(1000);//点击设置面板上的控件之前需要等待settingPanel动画的完成
        onView(withId(R.id.tb_mic)).perform(click());
        onView(withId(R.id.tv_publish_settings)).perform(click());
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
