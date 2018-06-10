//
// Created by Youngjoo Park on 6/4/18.
//

#include <jni.h>
#include <shapes/triangle.h>

#include "glesNative.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
GLESNative *gGlesObject;


JNIEXPORT void JNICALL
Java_com_sonos_youngjoopark_nativetest_GLESContextActivity_CreateObjectNative(JNIEnv *env,
                                                                              jobject instance) {
    gGlesObject = new GLESNative();
    MyLOGW("GLESNativeObject created..");
}

JNIEXPORT void JNICALL
Java_com_sonos_youngjoopark_nativetest_GLESContextActivity_DeleteObjectNative(JNIEnv *env,
                                                                              jobject instance) {
    if(gGlesObject != NULL) {
        delete gGlesObject;
    }
    gGlesObject = NULL;
}

JNIEXPORT jboolean JNICALL
Java_com_sonos_youngjoopark_nativetest_GLESContextActivity_IsInitsDoneNative(JNIEnv *env,
                                                                             jobject instance) {
    if (gGlesObject == NULL || !gGlesObject->IsInitsDone()) {
       return JNI_FALSE;
    } else {
        return JNI_TRUE;
    }
}

JNIEXPORT jstring JNICALL
Java_com_sonos_youngjoopark_nativetest_GLESContextActivity_GetGLESVersionNative(JNIEnv *env,
                                                                                jobject instance) {
    std::string version = "";
    if (gGlesObject == NULL) {
       return env->NewStringUTF(version.c_str());
    }
    version = gGlesObject->GetGLESVersionInfo();
    return env->NewStringUTF(version.c_str());
}
*/
#ifdef  __cplusplus
};
#endif