//
// Created by Youngjoo Park on 6/7/18.
//

#include <jni.h>
#include "cube.h"
#include "MyJNIShaderHelper.h"


#ifdef __cplusplus
extern "C" {
#endif

extern Cube *gGLObject;

JNIEXPORT void JNICALL
Java_com_sonos_youngjoopark_ObjModelTest_Gestures_doubleTapNative(JNIEnv *env, jobject instance) {
    if (gGLObject == NULL) {
       return;
    }
    gGLObject->doubleTap();
}

JNIEXPORT void JNICALL
Java_com_sonos_youngjoopark_ObjModelTest_Gestures_scrollNative(JNIEnv *env, jobject instance,
                                                        jfloat distanceX, jfloat distanceY,
                                                        jfloat positionX, jfloat positionY) {
    if (gGLObject == NULL) {
        return;
    }

    // normalize movemenets on the screen with surface dimensions
    // invert dY since its coordinate direction is opposite..
    // i.e., top -> bottom on the screen is positive
    float dX = (float) distanceX / gGLObject->getScreenWidth();
    float dY = -(float) distanceY / gGLObject->getScreenHeight();
    float posX = 2 * positionX / gGLObject->getScreenWidth() - 1.0f;
    float posY = -2 * positionY / gGLObject->getScreenHeight() + 1.0f;
    posX = fmax(-1.0f, fmin(1.0f, posX));
    posY = fmax(-1.0f, fmin(1.0f, posY));
    gGLObject->scroll(dX, dY, posX, posY);
}

JNIEXPORT void JNICALL
Java_com_sonos_youngjoopark_nativetest_Gestures_scaleNative(JNIEnv *env, jobject instance, jfloat scaleFactor) {
    if (gGLObject == NULL) {
       return;
    }
    gGLObject->scale((float)scaleFactor);
}

JNIEXPORT void JNICALL
Java_com_sonos_youngjoopark_nativetest_Gestures_moveNative(JNIEnv *env, jobject instance,
                                                            jfloat distanceX, jfloat distanceY) {
    if (gGLObject == NULL) {
        return;
    }

    float dX = distanceX / gGLObject->getScreenWidth();
    float dY = distanceY / gGLObject->getScreenHeight();
    gGLObject->move(dX, dY);
}

#ifdef __cplusplus
};
#endif
