package com.renxl.jniapp;

/**
 * Created by renxuelong on 2019-05-22
 */
public class JniUtils extends JniParent {

    static {
        System.loadLibrary("jni_test");
    }

    public JniUtils() {
    }

    public JniUtils(String arg) {
        this.accessedStringField = arg;
    }

    private String accessedStringField = "accessField";

    public static int accessedStaticIntField = 0;

    public int getUserId() {
        return 0;
    }

    public static String isEnable(boolean param) {
        return param ? "true" : "false";
    }

    // 静态方法生成的头文件分钟方法的参数为 jclass
    public static native String getJniString();

    // 非静态方法生成的头文件分钟方法的参数为 jobject
    public native String accessField();

    public static native void accessStaticField();

    public native String accessMethod();

    public static native String accessStaticMethod();

    public native String accessParentMethod();

    public native String[] getStringArray();
}
