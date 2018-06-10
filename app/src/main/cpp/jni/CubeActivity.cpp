//
// Created by Youngjoo Park on 6/7/18.
//

#include <jni.h>
#include "cube.h"
#include "MyJNIShaderHelper.h"

#ifdef __cplusplus
extern "C" {
#endif

Cube *gGLObject = NULL;
MyJNIShaderHelper *gHelper = NULL;

JNIEXPORT void JNICALL
Java_com_sonos_youngjoopark_nativetest_CubeActivity_CreateObjectNative(JNIEnv *env,
                                                                       jobject instance,
                                                                       jobject assetManager,
                                                                       jstring pathToInternalDir){
    MyLOGI("CreateObjectNative called with path %s..", pathToInternalDir);
    gHelper = new MyJNIShaderHelper(env, instance, assetManager, pathToInternalDir);
    gGLObject = new Cube();
}

JNIEXPORT void JNICALL
Java_com_sonos_youngjoopark_nativetest_CubeActivity_DeleteObjectNative(JNIEnv *env, jobject instance) {
    if (gGLObject != NULL) {
        delete gGLObject;
    }
    gGLObject = NULL;

    if (gHelper != NULL) {
        delete gHelper;
    }
    gHelper = NULL;
}

#ifdef __cplusplus
};
#endif