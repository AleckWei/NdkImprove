#include <jni.h>
#include "android/log.h"
#include <stdio.h>
#include <string>

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("ndkimprove");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("ndkimprove")
//      }
//    }

// 定义log
#ifndef LOG_TAG
#define LOG_TAG "WWJ_JNI_TAG"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, __VA_ARGS__)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 调用此方法的类名
 */
static const char *className = "com/wwj/ndkimprove/JniInterfaceUtil";

static jstring stringFromCpp(JNIEnv *env, jobject thiz) {
    LOGD("jni call stringFromCpp method");
    const char *hello = "Hello from cpp";
    return env->NewStringUTF(hello);
}

/**
 * 将java方法对应映射到jni的方法中
 */
static JNINativeMethod jni_methods_table[] = {
        {"getStringFromCpp", "()Ljava/lang/String;", (void *) stringFromCpp},
};

static int
registerNativeMethods(JNIEnv *env, const char *className, const JNINativeMethod *gMethods,
                      int methodNum) {
    jclass clazz;
    LOGI("Registering %s native\n", className);
    clazz = env->FindClass(className);

    if (clazz == nullptr) {
        LOGE("Native registration unable to find class %s \n", className);
        return JNI_ERR;
    }

    if (env->RegisterNatives(clazz, gMethods, methodNum) < 0) {
        LOGE("Register natives failed for %s \n", className);
        return JNI_ERR;
    }

    env->DeleteLocalRef(clazz);
    return JNI_OK;
}

/**
 * jni初始化时会回调的函数，方法名得和jni.h中的一致，否则调用不到
 * @param vm 虚拟机环境
 * @param reserved
 * @return
 */
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("call JNI_OnLoad");

    // 先声明一个JNIEnv(jni函数映射堆栈)
    JNIEnv *env = nullptr;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return JNI_EVERSION;
    }

    registerNativeMethods(env, className, jni_methods_table,
                          sizeof(jni_methods_table) / sizeof(JNINativeMethod));

    return JNI_VERSION_1_4;
}

/**
 * 静态注册stringFromJni方法
 * @return jni自己处理的string，当前是“Hello from JNI”
 */
JNIEXPORT jstring JNICALL
Java_com_wwj_ndkimprove_MainActivity_stringFromJni(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from JNI";
    return env->NewStringUTF(hello.c_str());
}

#ifdef __cplusplus
}
#endif