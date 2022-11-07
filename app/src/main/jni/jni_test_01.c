//
// Created by renxuelong on 2019-05-21.
//
#include <stdio.h>
#include "com_renxl_jniapp_JniUtils.h"
#include <android/log.h> // 打印日志时需要引入 android/log.h

#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"hello",FORMAT,__VA_ARGS__)
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"hello",FORMAT,__VA_ARGS__)

JNIEXPORT jstring JNICALL Java_com_renxl_jniapp_JniUtils_getJniString
        (JNIEnv *env, jclass jcls) {
    return (*env)->NewStringUTF(env, "Hello JNI");
}

// C/C++访问Java的成员

// 1.访问属性
// 修改属性, public private 的都可以访问到
JNIEXPORT jstring JNICALL Java_com_renxl_jniapp_JniUtils_accessField
        (JNIEnv *env, jobject jobj) {
    // jobj 是对象, C 代码中访问 JNIEnv 的方法需要传如 env
    // 通过 GetObjectClass 方法可以由 jobject 获得 jclass
    jclass cls = (*env)->GetObjectClass(env, jobj);

    // 获取 jfieldID, 属性名称，属性签名
    jfieldID fid = (*env)->GetFieldID(env, cls, "accessedStringField", "Ljava/lang/String;");

    // 获取属性的值
    jstring jstr1 = (*env)->GetObjectField(env, jobj, fid);

    // 修改属性的值
    jstring jstr2 = (*env)->NewStringUTF(env, "accessedStringField");
    (*env)->SetObjectField(env, jobj, fid, jstr2);
    jstring jresult = (*env)->GetObjectField(env, jobj, fid);
    return jstr2;
}

JNIEXPORT void JNICALL Java_com_renxl_jniapp_JniUtils_accessStaticField
        (JNIEnv *env, jclass jcls) {
    // 获取静态属性的 jfieldID
    jfieldID fid = (*env)->GetStaticFieldID(env, jcls, "accessedStaticIntField", "I");
    // 获取静态属性的值
    jint jint1 = (*env)->GetStaticIntField(env, jcls, fid);
    jint result = jint1 + 10;
    // 修改静态成员的值
    (*env)->SetStaticIntField(env, jcls, fid, result);
}

JNIEXPORT jstring JNICALL Java_com_renxl_jniapp_JniUtils_accessMethod
        (JNIEnv *env, jobject jobj) {
    // jclass
    jclass jcls = (*env)->GetObjectClass(env, jobj);
    // 获取 jmethodID
    jmethodID jmId = (*env)->GetMethodID(env, jcls, "getUserId", "()I");

    // 调用 Java 方法时，有多个类型的 CallXXXMethod
    jint id = (*env)->CallIntMethod(env, jobj, jmId);
    if (id == 0) {
        jstring result = (*env)->NewStringUTF(env, "UserId：0");
        return result;
    } else {
        jstring result = (*env)->NewStringUTF(env, "UserId：1");
        return result;
    }
}

JNIEXPORT jstring JNICALL Java_com_renxl_jniapp_JniUtils_accessStaticMethod
        (JNIEnv *env, jclass jcls) {
    jmethodID jmId = (*env)->GetStaticMethodID(env, jcls, "isEnable", "(Z)Ljava/lang/String;");
    jboolean param = 1;
    jstring str = (*env)->CallStaticObjectMethod(env, jcls, jmId, param);
    return str;
}

JNIEXPORT jobjectArray JNICALL Java_com_renxl_jniapp_JniUtils_accessParentMethod
        (JNIEnv *env, jobject jobj) {
    // 根据类名找到 jclass
    jclass jcls = (*env)->FindClass(env, "com/renxl/jniapp/JniUtils");
    if (jcls == NULL) {
        jstring result = (*env)->NewStringUTF(env, "找不到指定类");
        return result;
    }

    // 访问构造方法时需要找到 <init> 方法
    jmethodID jmId = (*env)->GetMethodID(env, jcls, "<nit>", "(Ljava/lang/String;)V");
    // 是实例化一个对象
    jstring param = (*env)->NewStringUTF(env, "CallInitMethod");



    jobject jobject1 = (*env)->NewObject(env, jcls, jmId, param);

    // 调用父类方法
    jclass jcls_parent = (*env)->FindClass(env, "com/renxl/jniapp/JniParent");
    if (jcls_parent == NULL) {
        jstring result = (*env)->NewStringUTF(env, "找不到父类");
        return result;
    }

    jmethodID jpId = (*env)->GetMethodID(env, jcls_parent, "getCustomName", "()Ljava/lang/String;");
    jstring result = (*env)->CallObjectMethod(env, jobject1, jpId);
    return result;
}

JNIEXPORT jobjectArray JNICALL Java_com_renxl_jniapp_JniUtils_getStringArray
        (JNIEnv *env, jobject jobj) {

}