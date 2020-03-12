package com.zego.livedemo5;

import android.app.Activity;
import android.support.test.espresso.contrib.RecyclerViewActions;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.matcher.ViewMatchers.hasDescendant;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static android.support.test.espresso.matcher.ViewMatchers.withText;
import static com.zego.livedemo5.tools.CommonTools.printLog;
import static com.zego.livedemo5.tools.CommonTools.sleep;
import static com.zego.livedemo5.tools.PermissionTool.allowPermissionIfNeed;
import static com.zego.livedemo5.tools.ViewActionsEx.check;

/**
 * Created by realuei on 2017/4/28.
 */

@RunWith(AndroidJUnit4.class)
public class SpecialInstrumentedTest {
    @Rule
    public ActivityTestRule<MainActivity> mActivityRule = new ActivityTestRule<>(MainActivity.class);

    @BeforeClass
    static public void setUp() {
        _printLog("setUp");
        _printLog("process Id is: %s", android.os.Process.myPid());
    }

    @AfterClass
    static public void tearDown() {
        _printLog("tearDown");
    }

    @Test
    public void testPublish() {
        _printLog("testPublish");
        preparePublish();
        PublishInstrumentedTest.startPublishStream("testSingleAnchor", R.id.tv_select_single_anchor);
        PublishInstrumentedTest.waitForPublishSuccess(10000, mActivityRule.getActivity());
        sleep(11 * 60 * 1000);
        PublishInstrumentedTest.exitLive();
    }

    @Test
    public void testPublishOnlyMic() {
        _printLog("testPublishOnlyMic");
        preparePublish();
        PublishInstrumentedTest.startPublishStream("testSingleAnchor", R.id.tv_select_single_anchor);
        PublishInstrumentedTest.waitForPublishSuccess(10000, mActivityRule.getActivity());
        updateSetting(Integer.valueOf("100", 2));
        sleep(11 * 60 * 1000);
        PublishInstrumentedTest.exitLive();
    }

    @Test
    public void testPublishOnlyCamera() {
        _printLog("testPublishOnlyCamera");
        preparePublish();
        PublishInstrumentedTest.startPublishStream("testSingleAnchor", R.id.tv_select_single_anchor);
        PublishInstrumentedTest.waitForPublishSuccess(10000, mActivityRule.getActivity());
        updateSetting(Integer.valueOf("11", 2));
        sleep(11 * 60 * 1000);
        PublishInstrumentedTest.exitLive();
    }

    @Test
    public void testPublishOnJoin() {
        _printLog("testPublishOnJoin");
        preparePublish();
        PublishInstrumentedTest.startPublishStream("testSingleAnchor", R.id.tv_select_more_anchors);
        PublishInstrumentedTest.waitForPublishSuccess(10000, mActivityRule.getActivity());
        sleep(11 * 60 * 1000);
        PublishInstrumentedTest.exitLive();
    }

    @Test
    public void testPlay() {
        _printLog("testPlay");
        preparePlay();
        onView(withId(R.id.rlv_room_list)).perform(RecyclerViewActions.actionOnItem(hasDescendant(withText("testSingleAnchor")), click()));
        sleep(11 * 60 * 1000);
        PublishInstrumentedTest.exitLive();
    }

    @Test
    public void testAddJoin() {
        _printLog("testAddJoin");
        preparePlay();
        onView(withId(R.id.rlv_room_list)).perform(RecyclerViewActions.actionOnItem(hasDescendant(withText("testMoreAnchors")), click()));
        PublishInstrumentedTest.waitForPublishSuccess(10 * 1000, mActivityRule.getActivity());
        onView(withId(R.id.tv_publish_control)).perform(click());
        sleep(11 * 60 * 1000);
        PublishInstrumentedTest.exitLive();
    }

    static private void _printLog(String format, Object... args) {
        StringBuilder stringBuilder = new StringBuilder("%s_");
        stringBuilder.append(format);
        printLog(stringBuilder.toString(), "SpecialInstrumentedTest", args);
    }

    private void preparePublish() {
        Activity activity = mActivityRule.getActivity();
        onView(withText(activity.getResources().getStringArray(R.array.navigation_bar_titles)[1])).perform(click());
        allowPermissionIfNeed(); // 在有弹出音视频权限对话框时，点击同意
    }

    private void preparePlay() {
        Activity activity = mActivityRule.getActivity();
        onView(withText(activity.getResources().getStringArray(R.array.navigation_bar_titles)[0])).perform(click());
    }

    static private int[] SETTING_BUTTON_IDs = new int[] {
            R.id.tb_camera, R.id.tb_front_cam, R.id.tb_mic, R.id.tb_torch, R.id.tb_background_music
    };

    private void updateSetting(int combIndex) {
        onView(withId(R.id.tv_publish_settings)).perform(click());
        for (int i = 0; i < SETTING_BUTTON_IDs.length; i++) {
            if (((1 << i) & combIndex) != 0) {
                onView(withId(SETTING_BUTTON_IDs[i])).perform(check(true));
            } else {
                onView(withId(SETTING_BUTTON_IDs[i])).perform(check(false));
            }
        }
        onView(withId(R.id.tv_publish_settings)).perform(click());
    }
}
