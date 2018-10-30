package com.zego.livedemo5.entities;

/**
 * Created by zego on 2018/9/5.
 */

public class AppConfig {


    public long getAppid() {
        return appid;
    }

    public void setAppid(long appid) {
        this.appid = appid;
    }

    public String getAppkey() {
        return appkey;
    }

    public void setAppkey(String appkey) {
        this.appkey = appkey;
    }

    public int getBusinesstype() {
        return businesstype;
    }

    public void setBusinesstype(int businesstype) {
        this.businesstype = businesstype;
    }

    public boolean isTestenv() {
        return testenv;
    }

    public void setTestenv(boolean testenv) {
        this.testenv = testenv;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public long appid;
    public String appkey;
    public int businesstype;
    public boolean testenv;
    public String title;

    public boolean isI18n() {
        return i18n;
    }

    public void setI18n(boolean i18n) {
        this.i18n = i18n;
    }

    public boolean i18n;


}
