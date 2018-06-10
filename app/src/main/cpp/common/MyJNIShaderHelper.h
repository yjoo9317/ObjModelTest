//
// Created by yjoo9 on 6/4/2018.
//

#ifndef NATIVETEST_MY_JNI_SHADER_HELPER_H
#define NATIVETEST_MY_JNI_SHADER_HELPER_H
#include "myLogger.h"
#include "simpleGLM.h"
#include <android_native_app_glue.h>
#include <pthread.h>
#include <string>
#include <jni.h>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

class MyJNIShaderHelper {
private:
    mutable pthread_mutex_t pthreadMutex;
    std::string androidPath;
    AAssetManager *aAssetManager;
    std::string getFileName(std::string fileName);
    void printGLMMat4(glm::mat4 matrix);

public:
    MyJNIShaderHelper(JNIEnv *env, jobject obj, jobject assetManager, jstring path);
    ~MyJNIShaderHelper();

    //void init(JNIEnv *env, jobject obj, jobject assetManager, jstring path);

    bool retrieveFileName(std::string assetName, std::string &fileName,
                            bool checkIsFileNameAvailable = false);
    //bool transferToBuffer(const char *fileName, std::vector<uint8_t> *buffer);
};

extern MyJNIShaderHelper *gHelper;

#ifdef __cplusplus
};
#endif

#endif //NATIVETEST_MYJNISHADERHELPER_H
