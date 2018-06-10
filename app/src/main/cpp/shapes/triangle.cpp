//
// Created by Youngjoo Park on 6/4/18.
//

#include "triangle.h"
#include "myShader.h"
#include "math.h"

Triangle::Triangle() {
    initDone = false;
}

void Triangle::initGL() {
    NativeGLInit();

    static const GLfloat vertexBufferData[] = {
            // x      y    z     w
             0.0f,  0.5f, 0.0f, 1.0f, // top
            -0.5f, -0.5f, 0.0f, 1.0f, // bottom left
             0.5f, -0.5f, 0.0f, 1.0f  // bottom right
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_DYNAMIC_DRAW);

    static const GLfloat colorBufferData[] = {
            // r    g    b     alpha
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f
    };

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

    std::string vertexShader = "triangle_vertex.glsl";
    std::string fragmentShader = "triangle_fragment.glsl";

    shaderProgramID = loadShaders(vertexShader, fragmentShader);

    vertexAttribute = getAttributeLocation(shaderProgramID, "vertexPosition");
    colorAttribute = getAttributeLocation(shaderProgramID, "vertexColor");

    triangleVertexDelta = 0;
    triangleSwapRate = 0.01;

    CheckGLError("Triangle::initGL");
    initDone = true;
}

void Triangle::renderTriangle() {
    glUseProgram(shaderProgramID);

    // enable vertex buffer
    glEnableVertexAttribArray(vertexAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //--------------------------------------------------------------------------
    // in shader: gl_
    glVertexAttribPointer(vertexAttribute, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    //--------------------------------------------------------------------------

    // enable color buffer
    glEnableVertexAttribArray(colorAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    //--------------------------------------------------------------------------
    // in shader: gl_FragColor = vertexColor
    glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    //---------------------------------------------------------------------------

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(vertexAttribute);
    glDisableVertexAttribArray(colorAttribute);
}

void Triangle::animateTriangle() {

}

void Triangle::Render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderTriangle();
    //animateTriangle();
    CheckGLError("Triangle::Render");
}

void Triangle::SetViewport(int width, int height) {

    glViewport(0, 0, width, height);
    CheckGLError("Triangle::SetViewPort");
}