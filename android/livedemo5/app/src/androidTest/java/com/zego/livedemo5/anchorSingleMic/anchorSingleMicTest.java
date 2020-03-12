package com.zego.livedemo5.anchorSingleMic;

import android.app.Activity;
import android.support.test.rule.ActivityTestRule;

import com.zego.livedemo5.MainActivity;
import com.zego.livedemo5.R;
import com.zego.livedemo5.testPerformance.anchorMicInstrumentedTest;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Suite;

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

/**
 * Created by realuei on 2017/3/16.
 */

@RunWith(Suite.class)
@Suite.SuiteClasses({anchorMicInstrumentedTest.class})
public class anchorSingleMicTest {

}
