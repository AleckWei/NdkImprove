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

    public JniInterfaceUtil getsInstance() {
        synchronized (this) {
            if (sInstance == null) {
                sInstance = new JniInterfaceUtil();
            }
            return sInstance;
        }
    }

    public String getString() {
        return getStringFromCpp();
    }

    public native String getStringFromCpp();

}
