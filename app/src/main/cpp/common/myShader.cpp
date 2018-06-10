//
// Created by yjoo9 on 6/4/2018.
//

#include "myShader.h"
#include "MyJNIShaderHelper.h"
#include <iostream>
#include <fstream>


bool readShaderFile(std::string & shaderCode, std::string & shaderFile) {

    MyLOGI("read shader file from %s", shaderFile.c_str());
    bool isPresent = gHelper->retrieveFileName(shaderFile, shaderFile);
    if(!isPresent) {
        return false;
    }
    std::ifstream shaderStream(shaderFile.c_str(), std::ios::in);
    if (shaderStream.is_open()) {
       std::string Line = "";
        while(getline(shaderStream, Line)) {
            shaderCode += "\n"+Line;
            MyLOGI("code read: %s", Line.c_str());
        }
        shaderStream.close();
    } else {
        MyLOGE("Cannot open %s", shaderFile.c_str());
        return false;
    }
    MyLOGI("File %s read successfully.", shaderFile.c_str());
    return true;
}

bool compileShaderCode(GLuint & shaderId, const GLenum type, std::string code) {

    shaderId = glCreateShader(type);

    char const* source = code.c_str();
    // bind shader id and source
    glShaderSource(shaderId, 1, &source, NULL);
    // compile shader source code
    glCompileShader(shaderId);

    GLint result = GL_FALSE;
    int infoLength;
    // get compile result
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLength);
    if(result == GL_FALSE) {
        MyLOGI("Failed to compile shader");
        std::vector<char> shaderErrorLog(infoLength+1);
        glGetShaderInfoLog(shaderId, infoLength, NULL, &shaderErrorLog[0]);
        MyLOGI("%s", &shaderErrorLog[0]);
        return false;
    } else {
        MyLOGI("Compiled shader successfully");
    }
    return true;
}

bool linkProgram(GLuint programId, GLuint vertexShaderId, GLuint fragmentShaderId) {
    GLint result = GL_FALSE;

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId); // Shaders join in the program

    glGetProgramiv(programId, GL_LINK_STATUS, &result);

    // delete shader and will removed actually when shader was detached from the program
    if(vertexShaderId) {
        glDeleteShader(vertexShaderId);
    }
    if(fragmentShaderId) {
        glDeleteShader(fragmentShaderId);
    }

    if (result == GL_FALSE) {
        MyLOGI("Failed to link program");
        if(programId) {
            glDeleteProgram(programId);
        }
        return false;
    }

    MyLOGI("Program linked successfully.");

    return true;
}

GLuint loadShaders(std::string vertexShaderFile, std::string fragmentShaderFile) {
    GLuint vertexShaderId, fragmentShaderId, programId;
    programId = glCreateProgram();

    // reade and compile vertex shader code
    std::string vertexShaderCode;
    if(!readShaderFile(vertexShaderCode, vertexShaderFile)) {
        MyLOGE("Failed to read vertex shader file %s", vertexShaderFile.c_str());
        return 0;
    }
    if(!compileShaderCode(vertexShaderId, GL_VERTEX_SHADER, vertexShaderCode)) {
        MyLOGE("Failed to compile vertex shader code.");
        return 0;
    }

    // reade and compile fragment shader code
    std::string fragmentShaderCode;
    if(!readShaderFile(fragmentShaderCode, fragmentShaderFile)) {
        MyLOGE("Failed to read fragment shader file %s", fragmentShaderFile.c_str());
        return 0;
    }
    if(!compileShaderCode(fragmentShaderId, GL_FRAGMENT_SHADER, fragmentShaderCode)) {
        MyLOGE("Failed to compile fragment shader code.");
        return 0;
    }

    if(!linkProgram(programId, vertexShaderId, fragmentShaderId)) {
        MyLOGE("Failed to link shaders to program.");
        return 0;
    }

    return programId;
}

GLuint getAttributeLocation(GLuint programId, std::string attr) {
    GLint location = glGetAttribLocation(programId, attr.c_str());
    if (location == -1) {
        MyLOGF("Failed to get attr location of %s.", attr.c_str());
        return 0;
    } else {
        return (GLuint) location;
    }
}

