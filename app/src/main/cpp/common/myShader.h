//
// Created by yjoo9 on 6/4/2018.
//

#ifndef NATIVETEST_MYSHADER_H
#define NATIVETEST_MYSHADER_H

#include <string>
#include "glesNative.h"
#include "myLogger.h"
GLuint loadShaders(std::string vertexShaderCode, std::string fragmentShaderCode);
GLuint getAttributeLocation(GLuint programId, std::string attributeName);

#endif //NATIVETEST_MYSHADER_H
