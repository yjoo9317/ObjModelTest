//
// Created by Youngjoo Park on 6/6/18.
//

#ifndef NATIVETEST_CUBE_H
#define NATIVETEST_CUBE_H

#include "myLogger.h"
#include "glesNative.h"
#include "MyCamera.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>

class Cube {
public:
    Cube();
    ~Cube();
    void initGL();
    void Render();
    void SetViewPort(int width, int height);
    bool InitsDone() { return initDone;}
    void doubleTap();
    void scroll(float distanceX, float distanceY, float positionX, float positionY);
    void scale(float scaleFactor);
    void move(float distanceX, float distanceY);
    int getScreenWidth() const { return screenWidth;}
    int getScreenHeight() const { return screenHeight; }

private:
    void renderCube();
    bool initDone;
    int screenWidth, screenHeight;
    std::vector<float> modelDefaultPosition;
    MyCamera *myCamera;

    GLuint vertexBuffer, colorBuffer;
    GLuint vertexAttributeLocation, colorAttributeLocation;
    GLuint programId;
    GLint mvpLocation;
};

#endif //NATIVETEST_CUBE_H
