//
// Created by Youngjoo Park on 6/4/18.
//

#ifndef NATIVETEST_TRIANGLE_H
#define NATIVETEST_TRIANGLE_H

#include "myLogger.h"
#include "glesNative.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string>

class Triangle {
public:
    Triangle();
    void    initGL();
    void    Render();
    void    SetViewport(int width, int height);
    bool    IsInitsDone() { return initDone; }

private:
    void    renderTriangle();
    void    animateTriangle();

    bool    initDone;

    // vertex buffer for triangle's vertices, colors
    GLuint  vertexBuffer, colorBuffer;
    // will hold attributed for shader variables
    GLuint  vertexAttribute, colorAttribute;
    GLuint  shaderProgramID;

    float   triangleVertexDelta, triangleSwapRate;

};

#endif //NATIVETEST_TRIANGLE_H
