package com.zego.livedemo5;

import android.support.test.espresso.contrib.RecyclerViewActions;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Ignore;
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

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class PlayInstrumentedTest {

    @Rule
    public ActivityTestRule<MainActivity> mActivityRule = new ActivityTestRule<>(MainActivity.class);

    @BeforeClass
    static public void setUp() {
        printLog("PlayInstrumentedTest_setUp");
        printLog("process Id is: %s", android.os.Process.myPid());
    }

    @Ignore
    @Test
    public void testEnterRoom() {
        printLog("PlayInstrumentedTest_testPublishStream");
        printLog("Activity's hasCode: %s; name: %s", mActivityRule.getActivity().hashCode(), mActivityRule.getActivity().getClass().getName());
        onView(withId(R.id.rlv_room_list)).perform(RecyclerViewActions.actionOnItem(hasDescendant(withText("DemoAutomator")), click()));
        sleep(100000);
    }

    @AfterClass
    static public void tearDown() {
        printLog("PlayInstrumentedTest_tearDown");
    }
}
