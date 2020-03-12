package com.zego.livedemo5.utils;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by zego on 2019/1/8.
 */

public class StringUtil {

    public static String replaceBlank(String str) {
        String dest = "";
        if (str!=null) {
            Pattern p = Pattern.compile("\\s*|\t|\r|\n");
            Matcher m = p.matcher(str);
            dest = m.replaceAll("");
        }
        return dest;
    }

}
