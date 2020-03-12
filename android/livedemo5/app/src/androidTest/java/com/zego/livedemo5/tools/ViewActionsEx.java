package com.zego.livedemo5.tools;

import android.support.test.espresso.UiController;
import android.support.test.espresso.ViewAction;
import android.support.test.espresso.action.ViewActions;
import android.support.test.espresso.matcher.ViewMatchers;
import android.view.View;
import android.widget.Checkable;
import android.widget.ProgressBar;
import android.widget.SeekBar;

import org.hamcrest.Description;
import org.hamcrest.Matcher;
import org.hamcrest.TypeSafeMatcher;

import java.util.Random;

import static android.support.test.espresso.core.deps.guava.base.Preconditions.checkArgument;
import static android.support.test.espresso.core.deps.guava.base.Preconditions.checkNotNull;

/**
 * Created by realuei on 2017/3/30.
 */

public final class ViewActionsEx {

    private static final int VIEW_DISPLAY_PERCENTAGE = 90;

    private ViewActionsEx() { }

    public static ViewAction enable() {
        return ViewActions.actionWithAssertions(new EnableAction(true));
    }

    public static ViewAction disable() {
        return ViewActions.actionWithAssertions(new EnableAction(false));
    }

    /**
     * the progress on a SeekBar
     * @param progress the value in (0, 100]
     * @return
     */
    public static ViewAction setProgress(final int progress) {
        return new ViewAction() {
            @Override
            public Matcher<View> getConstraints() {
                return ViewMatchers.isAssignableFrom(ProgressBar.class);
            }

            @Override
            public String getDescription() {
                return "set progress: " + progress;
            }

            @Override
            public void perform(UiController uiController, View view) {
                checkArgument(progress > 0 && progress <= 100, "progress value must in (0, 100], but the value is : " + progress);
                SeekBar sBar = (SeekBar)view;
                int maxProgress = sBar.getMax();
                int exceptProgress = maxProgress * progress / 100;
                sBar.setProgress(exceptProgress);
            }
        };
    }

    public static ViewAction check(final boolean checked) {
        return new ViewAction() {
            @Override
            public Matcher<View> getConstraints() {
                return new TypeSafeMatcher<View>() {
                    @Override
                    public void describeTo(Description description) {
                        description.appendText("is checkable");
                    }

                    @Override
                    public boolean matchesSafely(View view) {
                        return view instanceof Checkable;
                    }
                };
            }

            @Override
            public String getDescription() {
                return "set check state: " + checked;
            }

            @Override
            public void perform(UiController uiController, View view) {
                if (!view.isEnabled()) return;

                Checkable checkAble = (Checkable)view;
                if (checkAble.isChecked() == checked) return;

                checkAble.setChecked(checked);
            }
        };
    }

    private static class EnableAction implements ViewAction {
        private boolean mEnabled = true;

        public EnableAction(boolean enabled) {
            this.mEnabled = enabled;
        }

        @Override
        public Matcher<View> getConstraints() {
            return ViewMatchers.isDisplayingAtLeast(VIEW_DISPLAY_PERCENTAGE);
        }

        @Override
        public String getDescription() {
            return getClass().getName() + " " + String.valueOf(mEnabled);
        }

        @Override
        public void perform(UiController uiController, View view) {
            checkNotNull(uiController);
            checkNotNull(view);

            view.setEnabled(mEnabled);
        }
    }
}
