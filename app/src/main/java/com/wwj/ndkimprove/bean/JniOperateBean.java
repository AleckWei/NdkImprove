package com.wwj.ndkimprove.bean;

/**
 * @author WWJ
 * @detail: jni操作bean对象类
 * @date: 2023/11/3 15:03
 */
public class JniOperateBean {
    private int num = 35;

    public static String name = "WWJ";

    private final String packString = "hello world ";

    private String packMyString(String orginalString, int packNum) {
        return packString + orginalString + packNum;
    }

    public native int getNumPlusOne();

    public native void operatorStaticName();

    public native void accessPrivateNum();

    public native String accessPrivateMethod();

    public int getNum() {
        return num;
    }
}
