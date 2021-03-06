#include "jni_lib.h"

#define JNI_AN_MainActivity        "com/example/lee/testapp/MainActivity"

#define METHOD_NUM 1
JNINativeMethod g_nativeMethod[METHOD_NUM]={
        {"GetStrFromJNI","()Ljava/lang/String;",(void*)GetStrFromJNI}
};

/*
 * 被虚拟机自动调用
 */
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK)
        //return not JNI_OK, there is another thread executing this function, just cancel it
        return JNI_ERR;

    jclass jClass = env->FindClass(JNI_AN_MainActivity);
    env->RegisterNatives(jClass,g_nativeMethod,METHOD_NUM);
    env->DeleteLocalRef(jClass);
    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM* vm, void* reserved) {
    JNIEnv *env;
    int nJNIVersionOK = vm->GetEnv((void **)&env, JNI_VERSION_1_6) ;
    jclass jClass = env->FindClass(JNI_AN_MainActivity);
    env->UnregisterNatives(jClass);
    env->DeleteLocalRef(jClass);
}



jstring GetStrFromJNI(JNIEnv *env, jobject callObj) {
    return env->NewStringUTF("String From Jni With c++");
}