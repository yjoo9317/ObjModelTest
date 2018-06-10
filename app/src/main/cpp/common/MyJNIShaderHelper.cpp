//
// Created by yjoo9 on 6/4/2018.
//

#include "MyJNIShaderHelper.h"
#include "android/asset_manager_jni.h"

MyJNIShaderHelper::MyJNIShaderHelper(JNIEnv *env, jobject obj, jobject assetManager,
                                     jstring path) {

    aAssetManager = AAssetManager_fromJava(env, assetManager);

    const char *pathToInternalResDir;

    pathToInternalResDir = env->GetStringUTFChars(path, NULL);
    androidPath = std::string(pathToInternalResDir);
    env->ReleaseStringUTFChars(path, pathToInternalResDir);

    // setup a safe thread to touch the resource securely
    pthread_mutex_init(&pthreadMutex, NULL);
    MyLOGI("MyJNIShaderHelper created..");
}

MyJNIShaderHelper::~MyJNIShaderHelper() {

    // destroy mutex thread..
    pthread_mutex_destroy(&pthreadMutex);
}

bool MyJNIShaderHelper::retrieveFileName(std::string assetName, std::string &fileName,
                                     bool isFileAvailable) {
    fileName = androidPath+"/"+ getFileName(assetName);

    // if it was used previously and is in app's internal dir
    FILE *file = fopen(fileName.c_str(), "rb");
    if (file && isFileAvailable) {
        MyLOGI("Found the shader file : %s", fileName.c_str());
        fclose(file);
        pthread_mutex_unlock(&pthreadMutex);
        return true;
    }

    // then look for the file
    bool result = false;

    pthread_mutex_lock(&pthreadMutex);

    AAsset *asset = AAssetManager_open(aAssetManager, assetName.c_str(), AASSET_MODE_STREAMING);
    int length = AAsset_getLength(asset);
    MyLOGI("shader file length: %d", length);

    char buf[BUFSIZ];
    int nb_read = 0;
    if (asset != NULL) {
        FILE *out = fopen(fileName.c_str(), "w");
        while((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0) {
            MyLOGI("file read: %s", buf);
            fwrite(buf, nb_read, 1, out);
        }
        fclose(out);
        AAsset_close(asset);
        result = true;

        MyLOGI("Asset found : %s", fileName.c_str());
    } else {
        MyLOGI("Asset Not found : %s", fileName.c_str());
    }
    pthread_mutex_unlock(&pthreadMutex);
    return result;
}

std::string MyJNIShaderHelper::getFileName(std::string fileName) {
    // assume filename is of the form "<path>/<name>.<type>"
    std::string::size_type slashIndex = fileName.find_last_of("/");

    std::string onlyName;
    if (slashIndex == std::string::npos) {
        onlyName = fileName.substr(0, std::string::npos);
    } else {
        onlyName = fileName.substr(slashIndex + 1, std::string::npos);
    }

    return onlyName;
}

void MyJNIShaderHelper::printGLMMat4(glm::mat4 matrix) {
    MyLOGD("%f %f %f %f", matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0]);
    MyLOGD("%f %f %f %f", matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1]);
    MyLOGD("%f %f %f %f", matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2]);
    MyLOGD("%f %f %f %f", matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
}