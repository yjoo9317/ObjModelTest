//
// Created by Youngjoo Park on 6/1/18.
//

#include "glesNative.h"

/**
 * Checks for OpenGL errors.Very useful while debugging. Call it as often as required
 */
void CheckGLError(std::string funcName){

    GLenum err = glGetError();
    if (err == GL_NO_ERROR) {
        return;
    } else {
        MyLOGF("[FAIL GL] %s", funcName.c_str());
    }

    switch(err) {

        case GL_INVALID_ENUM:
            MyLOGE("GL_INVALID_ENUM: GLenum argument out of range");
            break;

        case GL_INVALID_VALUE:
            MyLOGE("GL_INVALID_VALUE: numeric argument out of range");
            break;

        case GL_INVALID_OPERATION:
            MyLOGE("GL_INVALID_OPERATION: operation illegal in current state");
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            MyLOGE("GL_INVALID_FRAMEBUFFER_OPERATION: framebuffer object is not complete");
            break;

        case GL_OUT_OF_MEMORY:
            MyLOGE( "GL_OUT_OF_MEMORY: not enough memory left to execute command");
            break;

        default:
            MyLOGE("unlisted error");
            break;
    }
}

void NativeGLInit() {

    // set black background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    CheckGLError("NativeGLInit");
}
/*
GLESNative::GLESNative() {
    initsDone = false;
    glesVersionInfo ="";
}


void GLESNative::initGL() {

    MyLOGW("PerformGLInits.");
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // load the GLES version into a string
    std::ostringstream version_string;
    version_string << glGetString(GL_VERSION) << ", " << glGetString(GL_SHADING_LANGUAGE_VERSION);
    glesVersionInfo = std::string(version_string.str());

    // check if the device supports GLES 3 or GLES 2
    const char* versionStr = (const char*)glGetString(GL_VERSION);

    initsDone = true;

    CheckGLError("GLESNative::PerformGLInits");
}


void GLESNative::Render() {

    // blue background
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CheckGLError("GLESNative::Render");

}

void GLESNative::SetViewport(int width, int height) {

    // set the viewport
    // function is also called when user changes device orientation
    glViewport(0, 0, width, height);

    CheckGLError("GLESNative::SetViewport");
}
*/