package com.zego.livedemo5.utils;

import org.json.JSONException;
import org.json.JSONTokener;

/**
 * Created by realuei on 2017/5/10.
 */

public final class JsonUtil {
    static public Object safeDecodeFromString(String content) {
        try {
            JSONTokener tokener = new JSONTokener(content);
            return tokener.nextValue();
        } catch (JSONException e) {
            return null;
        } catch (NullPointerException e) {
            return null;
        }
    }
}
