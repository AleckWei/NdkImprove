#include <jni.h>
#include <stdio.h>
#include <jni.h>
#include <string>
#include <jni.h>
#include <jni.h>

//
// Created by 560391 on 2023/11/3.
// java对象操作方法集合的c++文件
//

JNICALL JNIEXPORT
extern "C" jint
Java_com_wwj_ndkimprove_bean_JniOperateBean_getNumPlusOne(JNIEnv *env, jobject thiz) {
    // 获取到这个对象的类
    jclass clazz = env->GetObjectClass(thiz);
    // 获取这个属性的id
    jfieldID fid = env->GetFieldID(clazz, "num", "I");
    // 通过数据id获取到属性具体值
    jint num = env->GetIntField(thiz, fid);

    return ++num;
}

JNICALL JNIEXPORT
extern "C" void
Java_com_wwj_ndkimprove_bean_JniOperateBean_operatorStaticName(JNIEnv *env,
                                                               jobject thiz) {
    // 先获取到类对象
    jclass objectClass = env->GetObjectClass(thiz);
    // 通过类对象获取属性id
    jfieldID fid = env->GetStaticFieldID(objectClass, "name", "Ljava/lang/String;");
    // 通过数据id找到对应值
    jstring name = (jstring) env->GetStaticObjectField(objectClass, fid);

    const char *nameChar = env->GetStringUTFChars(name, JNI_FALSE);

    char newChar[30] = "hello ";
    strcat(newChar, nameChar);

    jstring newCharName = env->NewStringUTF(newChar);

    env->SetStaticObjectField(objectClass, fid, newCharName);
}


JNICALL JNIEXPORT
extern "C" void
Java_com_wwj_ndkimprove_bean_JniOperateBean_accessPrivateNum(JNIEnv *env,
                                                             jobject thiz) {
    jclass objectClazz = env->GetObjectClass(thiz);
    jfieldID fid = env->GetFieldID(objectClazz, "num", "I");

    jint num = env->GetIntField(thiz, fid);

    if (num > 30) {
        num--;
    } else {
        num++;
    }

    env->SetIntField(thiz, fid, num);
}

JNICALL JNIEXPORT
extern "C" jstring
Java_com_wwj_ndkimprove_bean_JniOperateBean_accessPrivateMethod(JNIEnv *env,
                                                                jobject thiz) {
    jclass objectClass = env->GetObjectClass(thiz);

    jmethodID methodId = env->GetMethodID(objectClass, "packMyString",
                                          "(Ljava/lang/String;I)Ljava/lang/String;");
    char charStr[15] = "is Handsome ";
    jstring packString = env->NewStringUTF(charStr);
    jint packNum = 20;

    jstring result = (jstring) env->CallObjectMethod(thiz, methodId, packString, packNum);
    return result;
}
