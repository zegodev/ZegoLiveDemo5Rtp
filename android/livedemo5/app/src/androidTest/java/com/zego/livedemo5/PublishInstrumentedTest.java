package com.zego.livedemo5;

import android.app.Activity;
import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.filters.LargeTest;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;
import android.support.test.uiautomator.UiDevice;
import android.support.test.uiautomator.UiObject;
import android.support.test.uiautomator.UiObjectNotFoundException;
import android.support.test.uiautomator.UiSelector;

import com.zego.livedemo5.tools.ViewMatchersEx;
import com.zego.livedemo5.tools.JoinLiveRequestMonitor;
import com.zego.livedemo5.tools.TrafficStatistics;
import com.zego.livedemo5.utils.PreferenceUtil;
import com.zego.zegoliveroom.ZegoLiveRoom;

import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.FixMethodOrder;
import org.junit.Ignore;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.MethodSorters;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.clearText;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.action.ViewActions.closeSoftKeyboard;
import static android.support.test.espresso.action.ViewActions.pressBack;
import static android.support.test.espresso.action.ViewActions.typeText;
import static android.support.test.espresso.matcher.ViewMatchers.withClassName;
import static android.support.test.espresso.matcher.ViewMatchers.withContentDescription;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static android.support.test.espresso.matcher.ViewMatchers.withParent;
import static android.support.test.espresso.matcher.ViewMatchers.withText;
import static com.zego.livedemo5.tools.CommonTools.printLog;
import static com.zego.livedemo5.tools.CommonTools.sleep;
import static com.zego.livedemo5.tools.ViewActionsEx.disable;
import static com.zego.livedemo5.tools.ViewActionsEx.enable;
import static com.zego.livedemo5.tools.PermissionTool.allowPermissionIfNeed;
import static org.hamcrest.Matchers.allOf;
import static org.junit.Assert.assertEquals;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
@FixMethodOrder(MethodSorters.DEFAULT)
@LargeTest
public class PublishInstrumentedTest {

    private Activity mActivity;

    private static String mOldUsername;
    @Rule
    public ActivityTestRule<MainActivity> mActivityRule = new ActivityTestRule<>(MainActivity.class);

    @BeforeClass
    static public void init() {
        printLog("PublishInstrumentedTest_init");

        //=====  临时代码 =====
        String testUserName = "DemoAutomator";
        mOldUsername = PreferenceUtil.getInstance().getUserName();
        PreferenceUtil.getInstance().setUserName(testUserName);
        String userId = PreferenceUtil.getInstance().getUserID();
        ZegoLiveRoom.setUser(userId, testUserName);
        //=====  临时代码 =====
    }

    @AfterClass
    static public void unInit() {
        printLog("PublishInstrumentedTest_unInit");
        PreferenceUtil.getInstance().setUserName(mOldUsername);
    }

    @Before
    public void setUp() {
        mActivity = mActivityRule.getActivity();
        onView(withText(mActivity.getResources().getStringArray(R.array.navigation_bar_titles)[1])).perform(click());
        allowPermissionIfNeed(); // 在有弹出音视频权限对话框时，点击同意
    }

    @Test
    public void testModifyNickName() {
        printLog("PublishInstrumentedTest_testModifyNickName");
        onView(allOf(withClassName(ViewMatchersEx.IMAGE_BUTTON_COMPAT), withParent(withId(R.id.toolbar)))).perform(click());
        onView(withId(R.id.et_user_name)).perform(enable(), clearText(), typeText("DemoAutomator"), disable());
        onView(allOf(withClassName(ViewMatchersEx.IMAGE_BUTTON_COMPAT), withParent(withId(R.id.toolbar)))).perform(click());
    }


    @Ignore
    @Test
    public void testSingleAnchorStream() {
        printLog("PublishInstrumentedTest_testSingleAnchorStream");
        startPublishStream("testSingleAnchor", R.id.tv_select_single_anchor);
        keepSilent();

        float[] usedBytes = monitorTrafficInTime(60);
        printLog("in single mode with 60s, send Bytes: %.2fKb; received Bytes: %.2fKb", usedBytes[0], usedBytes[1]);
        exitLive();
    }

    @Ignore
    @Test
    public void testMoreAnchorsStream() {
        printLog("PublishInstrumentedTest_testMoreAnchorsStream");
        startPublishStream("testMoreAnchors", R.id.tv_select_more_anchors);
        keepSilent();

        JoinLiveRequestMonitor monitor = monitorJoinLiveRequest();

        float[] usedBytes = monitorTrafficInTime(60);
        printLog("in more mode with 60s, send Bytes: %.2fKb; received Bytes: %.2fKb", usedBytes[0], usedBytes[1]);
        monitor.interrupt();
        exitLive();
    }

    @Ignore
    @Test
    public void testMixStream() {
        printLog("PublishInstrumentedTest_testMixStream");
        startPublishStream("testMixAnchors", R.id.tv_select_mix_stream);
        keepSilent();

        JoinLiveRequestMonitor monitor = monitorJoinLiveRequest();

        float[] usedBytes = monitorTrafficInTime(60);
        printLog("in mix mode with 60s, send Bytes: %.2fKb; received Bytes: %.2fKb", usedBytes[0], usedBytes[1]);
        monitor.interrupt();
        exitLive();
    }

    @Test
    public void testSingleAnchorWithSettings() {
        printLog("PublishInstrumentedTest_testSingleAnchorWithSettings");
        for (int settingCombinationIndex = 0; settingCombinationIndex < (1<< 8); settingCombinationIndex++) {
            int[] combinationIds = SettingsInstrumentedTest.modifyLiveSetting(settingCombinationIndex);
            startPublishStream("testSingleAnchor", R.id.tv_select_single_anchor);
            waitForPublishSuccess(10000, mActivity);
            exitLive();
            SettingsInstrumentedTest.resetLiveSetting(combinationIds);
        }
    }

    @Test
    public void testMoreAnchorsWithSettings() {
        printLog("PublishInstrumentedTest_testMoreAnchorsWithSettings");
        for (int settingCombinationIndex = 0; settingCombinationIndex < (1<< 8); settingCombinationIndex++) {
            int[] combinationIds = SettingsInstrumentedTest.modifyLiveSetting(settingCombinationIndex);
            startPublishStream("testMoreAnchors", R.id.tv_select_more_anchors);
            waitForPublishSuccess(10000, mActivity);
            exitLive();
            SettingsInstrumentedTest.resetLiveSetting(combinationIds);
        }
    }

    @Test
    public void testMixStreamWithSetting() {
        printLog("PublishInstrumentedTest_testMixStreamWithSetting");
        for (int settingCombinationIndex = 0; settingCombinationIndex < (1<< 8); settingCombinationIndex++) {
            int[] combinationIds = SettingsInstrumentedTest.modifyLiveSetting(settingCombinationIndex);
            startPublishStream("testMixAnchors", R.id.tv_select_mix_stream);
            waitForPublishSuccess(10000, mActivity);
            exitLive();
            SettingsInstrumentedTest.resetLiveSetting(combinationIds);
        }
    }

    static public void startPublishStream(String roomName, int btnResId) {
        onView(withId(R.id.et_publish_title)).perform(clearText(), typeText(roomName), closeSoftKeyboard());
        // 点击开始直播
        onView(withId(R.id.btn_start_publish)).perform(click());
        // 选择直播类型
        onView(withId(btnResId)).perform(click());
    }

    private void keepSilent() {
        onView(withId(R.id.tv_speaker)).perform(click());

        waitForPublishSuccess(5000, mActivity);    // 等待设置按钮可用(推流成功后才可点击)，此处因使用 IdlingResource 有难度

        onView(withId(R.id.tv_publish_settings)).perform(click());

        sleep(500); // 等待 SettingPanel 动画完成
        onView(withId(R.id.tb_mic)).perform(click(), pressBack());
    }

    /**
     * record the used traffic in special time and return the totoal traffic
     * @param seconds time
     * @return total used traffic int[] {send usage, received usage}
     */

    private float[] monitorTrafficInTime(int seconds) {
        TrafficStatistics trafficStatistics = new TrafficStatistics(android.os.Process.myUid());
        trafficStatistics.beginRecord();

        int i = seconds;
        while (i-- > 0) {
            sleep(1000);
        }
        trafficStatistics.stopRecord();
        return new float[] { trafficStatistics.getAppTotalTxKBytes(), trafficStatistics.getAppTotalRxKBytes() };
    }

    static public JoinLiveRequestMonitor monitorJoinLiveRequest() {
        JoinLiveRequestMonitor monitor = new JoinLiveRequestMonitor("joinLiveMonitor");
        monitor.start();
        return monitor;
    }

    static public void exitLive() {
        onView(withId(R.id.tv_close)).perform(click());
        onView(withText(R.string.Yes)).perform(click());
    }

    static public boolean waitForPublishSuccess(long timeout, Context context) {
        UiDevice uiDevice = UiDevice.getInstance(InstrumentationRegistry.getInstrumentation());
        UiObject settingTab = uiDevice.findObject(new UiSelector().className("android.widget.TextView").text(context.getString(R.string.publish_setting)).resourceId(context.getPackageName() + ":id/tv_publish_settings"));
        long usedTime = 0;
        boolean isTimeout = true;
        while (usedTime <= timeout) {
            try {
                if (settingTab.isEnabled()) {
                    isTimeout = false;
                    printLog("publish success, interrupt waiting");
                    break;
                }

                printLog("waiting for publish success");
            } catch (UiObjectNotFoundException e) {
                printLog("exception: %s", e);
            }

            sleep(500);
            usedTime += 500;
        }
        return isTimeout;
    }

}
