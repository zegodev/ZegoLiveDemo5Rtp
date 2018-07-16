package com.zego.livedemo5.tools;

import android.support.test.espresso.UiController;
import android.support.test.espresso.ViewAction;
import android.support.test.espresso.ViewInteraction;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import org.hamcrest.Matcher;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.matcher.ViewMatchers.isAssignableFrom;

/**
 * Created by realuei on 2017/3/20.
 */

public class ViewTool {
    public static String getTextFromEditText(final Matcher<View> matcher) {
        final String[] text = { null };
        ViewInteraction interaction = onView(matcher);
        if (interaction == null) return "";

        onView(matcher).perform(new ViewAction() {

            @Override
            public Matcher<View> getConstraints() {
                return isAssignableFrom(EditText.class);
            }

            @Override
            public String getDescription() {
                return "get text from a EditText";
            }

            @Override
            public void perform(UiController uiController, View view) {
                EditText et = (EditText)view;
                text[0] = et.getText().toString();
            }
        });
        return text[0];
    }

    public static String getTextFromTextView(final Matcher<View> matcher) {
        final String[] text = { null };
        ViewInteraction interaction = onView(matcher);
        if (interaction == null) return "";

        onView(matcher).perform(new ViewAction() {

            @Override
            public Matcher<View> getConstraints() {
                return isAssignableFrom(TextView.class);
            }

            @Override
            public String getDescription() {
                return "get text from a TextView";
            }

            @Override
            public void perform(UiController uiController, View view) {
                TextView tv = (TextView)view;
                text[0] = tv.getText().toString();
            }
        });
        return text[0];
    }
}
