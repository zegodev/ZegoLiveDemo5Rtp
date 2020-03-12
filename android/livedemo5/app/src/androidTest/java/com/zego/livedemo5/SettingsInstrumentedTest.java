package com.zego.livedemo5;

import android.support.test.filters.LargeTest;
import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

import com.zego.livedemo5.tools.ViewMatchersEx;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.Random;

import static android.support.test.espresso.Espresso.onData;
import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.action.ViewActions.scrollTo;
import static android.support.test.espresso.matcher.ViewMatchers.withClassName;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static android.support.test.espresso.matcher.ViewMatchers.withParent;
import static android.support.test.espresso.matcher.ViewMatchers.withText;
import static com.zego.livedemo5.tools.CommonTools.printLog;
import static com.zego.livedemo5.tools.ViewActionsEx.check;
import static com.zego.livedemo5.tools.ViewActionsEx.setProgress;
import static org.hamcrest.Matchers.allOf;
import static org.hamcrest.Matchers.instanceOf;
import static org.hamcrest.Matchers.is;

/**
 * Instrumentation test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
@LargeTest
public class SettingsInstrumentedTest {

    @Rule
    public ActivityTestRule<MainActivity> mActivityRule = new ActivityTestRule<>(MainActivity.class);

    @BeforeClass
    static public void setUp() {
        printLog("SettingsInstrumentedTest_setUp");
        printLog("process Id is: %s", android.os.Process.myPid());
    }

    @Test
    public void testModifyLiveQuality() {
        printLog("SettingsInstrumentedTest_testModifyLiveQuality");
        String[] qualityArray = mActivityRule.getActivity().getResources().getStringArray(R.array.resolution_types);
        for (int i = 0; i < qualityArray.length; i ++) {
            toggleSettingPanel();
            onView(withId(R.id.sp_resolutions)).perform(click());
            String quality = qualityArray[i];
//            onData(hasEntry(is(instanceOf(String.class)), is(quality))).perform(click());
            onData(allOf(is(instanceOf(String.class)), is(quality))).perform(click());
            if (i == qualityArray.length - 1) {
                int progress = new Random().nextInt(99) + 1;
                onView(withId(R.id.sb_resolution)).perform(setProgress(progress));
                progress = new Random().nextInt(99) + 1;
                onView(withId(R.id.sb_fps)).perform(setProgress(progress));
                progress = new Random().nextInt(99) + 1;
                onView(withId(R.id.sb_bitrate)).perform(setProgress(progress));
            }
            toggleSettingPanel();
        }
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings0_32() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings0_32");
        testModifyOtherSettings(0, 32);
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings32_64() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings32_64");
        testModifyOtherSettings(32, 64);
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings64_96() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings64_96");
        testModifyOtherSettings(64, 96);
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings96_128() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings96_128");
        testModifyOtherSettings(96, 128);
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings128_160() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings128_160");
        testModifyOtherSettings(128, 160);
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings160_176() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings160_192");
        testModifyOtherSettings(160, 176);
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings176_192() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings160_192");
        testModifyOtherSettings(176, 192);
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings192_224() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings192_224");
        testModifyOtherSettings(192, 224);
    }

    @Test
    @LargeTest
    public void testModifyOtherSettings224_256() {
        printLog("SettingsInstrumentedTest_testModifyOtherSettings224_256");
        testModifyOtherSettings(224, 256);
    }

    private static int[] SETTING_BUTTON_IDs = new int[] { R.id.tb_video_capture, R.id.tb_external_render,
            R.id.tb_video_filter, R.id.tb_hardware_encode, R.id.tb_hardware_decode,
            R.id.tb_rate_control, R.id.tb_preview_mirror, R.id.tb_capture_mirror};
    /**
     * ******************************************************************
     * 测试所有开头组合：
     *     基本思路：求全组合，则假设原有元素n个，则最终组合结果是2^n个。原因是：
     *     用位操作方法：假设元素原本有：a,b,c三个，则1表示取该元素，0表示不取。故去a则是001，取ab则是011.
     *     所以一共三位，每个位上有两个选择0,1.所以是2^n个结果。
     *     这些结果的位图值都是0,1,2....2^n。所以可以类似全真表一样，从值0到值2^n依次输出结果：即：
     *     000,001,010,011,100,101,110,111 。对应输出组合结果为：
     *         空,a, b ,ab,c,ac,bc,abc.
     *         这个输出顺序刚好跟数字0~2^n结果递增顺序一样
     *         取法的二进制数其实就是从0到2^n-1的十进制数
     * ******************************************************************
     *
     * 因发现一次性执行太多的操作，espresso 会异常，故分成若干段来执行
     */
    public static int[] modifyLiveSetting(int combIndex) {
        int maxCombCount = 1 << SETTING_BUTTON_IDs.length;
        if (combIndex >= maxCombCount) throw new RuntimeException("combIndex out of max combination rule: " + maxCombCount);
        int[] tempComb = new int[SETTING_BUTTON_IDs.length];
        StringBuilder msg = new StringBuilder();
        toggleSettingPanel();
        expandAdvanceItems();

        msg.setLength(0);
        msg.append("Num.").append(combIndex).append("==>");
        msg.append("setting comb: [");
        for (int j = 0; j < SETTING_BUTTON_IDs.length; j++) {
            if (((1 << j) & combIndex) != 0) {
                onView(withId(SETTING_BUTTON_IDs[j])).perform(scrollTo(), click());
                msg.append(j + 1).append("-<").append(SETTING_BUTTON_IDs[j]).append("> ");
                tempComb[j] = SETTING_BUTTON_IDs[j];
            }
        }
        msg.append(']');
        printLog(msg.toString());
        toggleSettingPanel();
        return tempComb;
    }

    public static void resetLiveSetting(int[] modifiedSettings) {
        toggleSettingPanel();
        for (int j = 0; j < modifiedSettings.length; j++) {
            // 恢复上次设置项
            if (modifiedSettings[j] > 0) {
                onView(withId(SETTING_BUTTON_IDs[j])).perform(scrollTo(), click());
                if (SETTING_BUTTON_IDs[j] == R.id.tb_preview_mirror) {
                    // tb_preview_mirror 默认为选中状态
                    onView(withId(modifiedSettings[j])).perform(scrollTo(), check(true));
//                        onView(withId(tempComb[j])).perform(scrollTo(), click()).check(matches(isChecked()));
                } else {
                    onView(withId(modifiedSettings[j])).perform(scrollTo(), check(false));
//                        onView(withId(tempComb[j])).perform(scrollTo(), click()).check(matches(isNotChecked()));
                }
                modifiedSettings[j] = 0;
            }
        }
        toggleSettingPanel();
    }

    private static void testModifyOtherSettings(int start, int end) {
        int combCount = 1 << SETTING_BUTTON_IDs.length;
        int[] tempComb = new int[SETTING_BUTTON_IDs.length];
        StringBuilder sb = new StringBuilder();
        for (int i = start; i < Math.min(end, combCount); i++) {
            int[] modifiedSettings = modifyLiveSetting(i);

            resetLiveSetting(modifiedSettings);
        }
    }

    private static void toggleSettingPanel() {
        onView(allOf(withClassName(ViewMatchersEx.IMAGE_BUTTON_COMPAT), withParent(withId(R.id.toolbar)))).perform(click());
    }

    private static void expandAdvanceItems() {
        onView(withId(R.id.tv_advanced)).perform(scrollTo(), click());
    }

    @AfterClass
    static public void tearDown() {
        printLog("PlayInstrumentedTest_tearDown");
    }
}
