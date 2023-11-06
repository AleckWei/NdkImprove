package com.wwj.ndkimprove;

/**
 * @author WWJ
 * @detail:
 * @date: 2023/11/1 16:38
 */
public class JniInterfaceUtil {

    private static JniInterfaceUtil sInstance;

    private JniInterfaceUtil() {
        if (sInstance != null) {
            throw new Error("do not reflect this class's instance");
        }
    }

    public static JniInterfaceUtil getsInstance() {
        synchronized (JniInterfaceUtil.class) {
            if (sInstance == null) {
                sInstance = new JniInterfaceUtil();
            }
            return sInstance;
        }
    }

    /**
     * 动态注册的方法
     *
     * @return 返回c++中写好的字符串
     */
    public String getString() {
        return getStringFromCpp();
    }

    private native String getStringFromCpp();

}
