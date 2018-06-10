//
// Created by Youngjoo Park on 6/1/18.
//

#ifndef NATIVETEST_GLESNATIVE_H
#define NATIVETEST_GLESNATIVE_H
#include <sstream>
#include <iostream>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>
#include <string>
#include "myLogger.h"


void NativeGLInit();
void CheckGLError(std::string funcName);

/*
class GLESNative {
public:
    GLESNative();
    void    initGL();
    void    Render();
    void    SetViewport(int width, int height);
    bool    IsInitsDone(){return initsDone;}
    std::string GetGLESVersionInfo() {return glesVersionInfo;}

private:
    bool    initsDone;
    std::string glesVersionInfo;
};
*/
#endif //NATIVETEST_GLESNATIVE_H
