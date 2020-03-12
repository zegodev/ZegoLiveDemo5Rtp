package com.zego.livedemo5.testPerformance;

import android.app.Activity;
import android.support.test.espresso.matcher.ViewMatchers;
import android.support.test.filters.LargeTest;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

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

/**
 * Created by cier on 2017/5/26.
 */
@RunWith(AndroidJUnit4.class)
@LargeTest
public class AudienceJoinPublishRoomTest {
    Activity mActivity;

    @Rule
    public ActivityTestRule<MainActivity> mMainActivity=new ActivityTestRule<MainActivity>(MainActivity.class);

    @BeforeClass
    public static void init(){
        printLog("AudienceJoinPublishRoomTest->init()");
    }

    @AfterClass
    public static void unInit(){
        printLog("AudienceJoinPublishRoomTest->unInit()");
    }

    @Before
    public void setup(){
        printLog("AudienceJoinPublishRoomTest->setup()");
        mActivity=mMainActivity.getActivity();
        sleep(30000);
    }

    @Test
    public void start(){
        onView(ViewMatchers.withText(anchorCameraInstrumentedTest.roomName)).perform(click());
        sleep(2000);
        onView(withId(R.id.tv_speaker)).perform(click());
        sleep(60*1000*(PerformanceTest.RUNTIME));
        endPublish();
    }

    public void endPublish(){
        onView(ViewMatchers.withId(R.id.tv_close)).perform(click());
    }
}
