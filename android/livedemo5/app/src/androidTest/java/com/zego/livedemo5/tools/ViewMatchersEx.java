package com.zego.livedemo5.tools;

import android.support.v7.widget.AppCompatImageButton;
import android.text.TextUtils;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.TextView;

import org.hamcrest.Description;
import org.hamcrest.Matcher;
import org.hamcrest.TypeSafeMatcher;

import java.util.ArrayList;
import java.util.List;

import static android.support.test.espresso.core.deps.guava.base.Preconditions.checkNotNull;

/**
 * Created by realuei on 2017/3/30.
 */

public final class ViewMatchersEx {
    public static Matcher<String> IMAGE_BUTTON = new GeneralMatcher(ImageButton.class.getName());
    public static Matcher<String> IMAGE_BUTTON_COMPAT = new GeneralMatcher(ImageButton.class.getName(), AppCompatImageButton.class.getName());

    public static Matcher<String> TEXT_VIEW = new GeneralMatcher(TextView.class.getName());

    public static Matcher<String> LIST_VIEW = new GeneralMatcher(ListView.class.getName());

    public static class GeneralMatcher extends TypeSafeMatcher<String> {
        private String mainClassName;
        private List<String> otherClassNames;

        private GeneralMatcher(String className, String... otherClassNames) {
            checkNotNull(className);

            mainClassName = className;
            this.otherClassNames = new ArrayList<>();
            for (int i = 0; otherClassNames != null &&  i < otherClassNames.length; i++) {
                if (TextUtils.isEmpty(otherClassNames[i])) continue;

                this.otherClassNames.add(otherClassNames[i]);
            }
        }

        @Override
        protected boolean matchesSafely(String item) {
            return mainClassName.equals(item) || matchOtherClasses(item);
        }

        @Override
        public void describeTo(Description description) {
            description.appendText(getClass().getName());
            description.appendText("_");
            description.appendText(mainClassName);

        }

        private boolean matchOtherClasses(String item) {
            for (int i = 0; item != null && i < otherClassNames.size(); i++) {
                if (item.equals(otherClassNames.get(i))) return true;
            }
            return false;
        }
    }
}
