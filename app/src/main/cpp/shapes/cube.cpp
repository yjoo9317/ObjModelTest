//
// Created by Youngjoo Park on 6/6/18.
//

#include "cube.h"
#include "myShader.h"


Cube::Cube() {
    MyLOGD("Cube create..");
    myCamera = new MyCamera();

    // create camera and place it at initial position
    float initPosition[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f};
    std::copy(&initPosition[0], &initPosition[5], std::back_inserter(modelDefaultPosition));
    myCamera->setModelPosition(modelDefaultPosition);
}

Cube::~Cube() {
    if(myCamera != NULL) {
        delete myCamera;
    }
}

void Cube::initGL() {
    NativeGLInit();

    //vec4 vertexPosition
    GLfloat cubeVertex[] = {

            -1.0f,-1.0f,-1.0f,  // face0 left
            -1.0f,-1.0f, 1.0f,  //     0
            -1.0f, 1.0f, 1.0f,  //     0
            -1.0f,-1.0f,-1.0f,  //     0
            -1.0f, 1.0f, 1.0f,  //     0
            -1.0f, 1.0f,-1.0f,  //     0
            1.0f,-1.0f,-1.0f,  // face1 right
            1.0f, 1.0f, 1.0f,  //     1
            1.0f,-1.0f, 1.0f,  //     1
            1.0f,-1.0f,-1.0f,  //     1
            1.0f, 1.0f,-1.0f,  //     1
            1.0f, 1.0f, 1.0f,  //     1
            1.0f,-1.0f, 1.0f,  // face2 down
            -1.0f,-1.0f,-1.0f,  //     2
            1.0f,-1.0f,-1.0f,  //     2
            -1.0f,-1.0f,-1.0f,  //     2
            1.0f,-1.0f, 1.0f,  //     2
            -1.0f,-1.0f, 1.0f,  //     2
            -1.0f, 1.0f, 1.0f,  // face3 top
            1.0f, 1.0f, 1.0f,  //     3
            -1.0f, 1.0f,-1.0f,  //     3
            -1.0f, 1.0f,-1.0f,  //     3
            1.0f, 1.0f, 1.0f,  //     3
            1.0f, 1.0f,-1.0f,  //     3
            1.0f, 1.0f, 1.0f,  // face4 front
            -1.0f, 1.0f, 1.0f,  //     4
            1.0f,-1.0f, 1.0f,  //     4
            -1.0f, 1.0f, 1.0f,  //     4
            -1.0f,-1.0f, 1.0f,  //     4
            1.0f,-1.0f, 1.0f,  //     4
            -1.0f, 1.0f,-1.0f,  // face5 back
            1.0f, 1.0f,-1.0f,  //     5
            1.0f,-1.0f,-1.0f,  //     5
            1.0f,-1.0f,-1.0f,  //     5
            -1.0f,-1.0f,-1.0f,  //     5
            -1.0f, 1.0f,-1.0f   //     5
            /*
        //    x      y      z     w
            -1.0f, -1.0f, -1.0f, 1.0f   // face0 left
            -1.0f, -1.0f,  1.0f, 1.0f   //     0
            -1.0f,  1.0f,  1.0f, 1.0f   //     0
            -1.0f, -1.0f, -1.0f, 1.0f   //     0
            -1.0f,  1.0f,  1.0f, 1.0f   //     0
            -1.0f,  1.0f, -1.0f, 1.0f,  //     0
             1.0f, -1.0f, -1.0f, 1.0f,  // face1 right
             1.0f,  1.0f,  1.0f, 1.0f,  //     1
             1.0f, -1.0f,  1.0f, 1.0f,  //     1
             1.0f, -1.0f, -1.0f, 1.0f,  //     1
             1.0f,  1.0f, -1.0f, 1.0f,  //     1
             1.0f,  1.0f,  1.0f, 1.0f,  //     1
             1.0f, -1.0f,  1.0f, 1.0f,  // face2 down
            -1.0f, -1.0f, -1.0f, 1.0f,  //     2
             1.0f, -1.0f, -1.0f, 1.0f,  //     2
            -1.0f, -1.0f, -1.0f, 1.0f,  //     2
             1.0f, -1.0f,  1.0f, 1.0f,  //     2
            -1.0f, -1.0f,  1.0f, 1.0f,  //     2
            -1.0f,  1.0f,  1.0f, 1.0f,  // face3 top
             1.0f,  1.0f,  1.0f, 1.0f,  //     3
            -1.0f,  1.0f, -1.0f, 1.0f,  //     3
            -1.0f,  1.0f, -1.0f, 1.0f,  //     3
             1.0f,  1.0f,  1.0f, 1.0f,  //     3
             1.0f,  1.0f, -1.0f, 1.0f,  //     3
             1.0f,  1.0f,  1.0f, 1.0f,  // face4 front
            -1.0f,  1.0f,  1.0f, 1.0f,  //     4
             1.0f, -1.0f,  1.0f, 1.0f,  //     4
            -1.0f,  1.0f,  1.0f, 1.0f,  //     4
            -1.0f, -1.0f,  1.0f, 1.0f,  //     4
             1.0f, -1.0f,  1.0f, 1.0f,  //     4
            -1.0f,  1.0f, -1.0f, 1.0f,  // face5 back
             1.0f,  1.0f, -1.0f, 1.0f,  //     5
             1.0f, -1.0f, -1.0f, 1.0f,  //     5
             1.0f, -1.0f, -1.0f, 1.0f,  //     5
            -1.0f, -1.0f, -1.0f, 1.0f,  //     5
            -1.0f,  1.0f, -1.0f, 1.0f   //     5
             */
    };

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertex), cubeVertex, GL_STATIC_DRAW);


    //vec4 fragmentColor
    GLfloat vertexColors[] = {
            1.0f, 0.0f, 0.0f, // red    - face0
            1.0f, 0.0f, 0.0f, //              0
            1.0f, 0.0f, 0.0f, //              0
            1.0f, 0.0f, 0.0f, //              0
            1.0f, 0.0f, 0.0f, //              0
            1.0f, 0.0f, 0.0f, //              0
            0.0f, 1.0f, 1.0f, // cyan   - face1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 0.0f, // green  - face2
            0.0f, 1.0f, 0.0f, //              2
            0.0f, 1.0f, 0.0f, //              2
            0.0f, 1.0f, 0.0f, //              2
            0.0f, 1.0f, 0.0f, //              2
            0.0f, 1.0f, 0.0f, //              2
            1.0f, 0.0f, 1.0f, // violet - face3
            1.0f, 0.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, //              3
            0.0f, 0.0f, 1.0f, // blue   - face4
            0.0f, 0.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, //              4
            1.0f, 1.0f, 0.0f, // yellow - face5
            1.0f, 1.0f, 0.0f, //              5
            1.0f, 1.0f, 0.0f, //              5
            1.0f, 1.0f, 0.0f, //              5
            1.0f, 1.0f, 0.0f, //              5
            1.0f, 1.0f, 0.0f, //              5

            /*
          // R     G     B    alpha
            1.0f, 0.0f, 0.0f, 1.0f, // red    - face0
            1.0f, 0.0f, 0.0f, 1.0f, //              0
            1.0f, 0.0f, 0.0f, 1.0f, //              0
            1.0f, 0.0f, 0.0f, 1.0f, //              0
            1.0f, 0.0f, 0.0f, 1.0f, //              0
            1.0f, 0.0f, 0.0f, 1.0f, //              0
            0.0f, 1.0f, 1.0f, 1.0f, // cyan   - face1
            0.0f, 1.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 1.0f, 1.0f, //              1
            0.0f, 1.0f, 0.0f, 1.0f, // green  - face2
            0.0f, 1.0f, 0.0f, 1.0f, //              2
            0.0f, 1.0f, 0.0f, 1.0f, //              2
            0.0f, 1.0f, 0.0f, 1.0f, //              2
            0.0f, 1.0f, 0.0f, 1.0f, //              2
            0.0f, 1.0f, 0.0f, 1.0f, //              2
            1.0f, 0.0f, 1.0f, 1.0f, // violet - face3
            1.0f, 0.0f, 1.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, 1.0f, //              3
            1.0f, 0.0f, 1.0f, 1.0f, //              3
            0.0f, 0.0f, 1.0f, 1.0f, // blue   - face4
            0.0f, 0.0f, 1.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, 1.0f, //              4
            0.0f, 0.0f, 1.0f, 1.0f, //              4
            1.0f, 1.0f, 0.0f, 1.0f, // yellow - face5
            1.0f, 1.0f, 0.0f, 1.0f, //              5
            1.0f, 1.0f, 0.0f, 1.0f, //              5
            1.0f, 1.0f, 0.0f, 1.0f, //              5
            1.0f, 1.0f, 0.0f, 1.0f, //              5
            1.0f, 1.0f, 0.0f, 1.0f  //              5
             */
    };

    // create vec4
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), vertexColors, GL_STATIC_DRAW);

    std::string vertexShader = "cube_vertex.glsl";
    std::string fragmentShader = "cube_fragment.glsl";

    programId = loadShaders(vertexShader, fragmentShader);

    vertexAttributeLocation = getAttributeLocation(programId, "vertexPosition");
    colorAttributeLocation = getAttributeLocation(programId, "vertexColor");
    mvpLocation = glGetUniformLocation(programId, "mvpMat");
    CheckGLError("Cube::initGL");
    initDone = true;
}

void Cube::renderCube() {

    glUseProgram(programId);

    glm::mat4 mvpMat = myCamera->getMVP();
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, (const GLfloat *) &mvpMat);

    glEnableVertexAttribArray(vertexAttributeLocation);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    //--------------------------------------------------------------------------
    // in shader: gl_Position = vertexPosition
    glVertexAttribPointer(vertexAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    //--------------------------------------------------------------------------

    glEnableVertexAttribArray(colorAttributeLocation);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    //--------------------------------------------------------------------------
    // in shader: gl_FragColor = vertexColor;
    glVertexAttribPointer(colorAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    //--------------------------------------------------------------------------

    glDrawArrays(GL_TRIANGLES, 0, 36); // 12 triangles * 3 vertices

    glDisableVertexAttribArray(vertexAttributeLocation);
    glDisableVertexAttribArray(colorAttributeLocation);
}

void Cube::Render() {

    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderCube();
    CheckGLError("Cube::Render");
}

void Cube::SetViewPort(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    glViewport(0, 0, width, height);
    CheckGLError("Cube::SetViewPort");

    myCamera->setAspectRatio((float) width / (float)height);
}

//--------------------------------------------------------------------------
// reset the position when double tapping.
//--------------------------------------------------------------------------
void Cube::doubleTap() {
    myCamera->setModelPosition(modelDefaultPosition);
}

//--------------------------------------------------------------------------
// rotate the model when scrolling
//--------------------------------------------------------------------------
void Cube::scroll(float distanceX, float distanceY, float positionX, float positionY) {
    myCamera->rotateModel(distanceX, distanceY, positionX, positionY);
}

//--------------------------------------------------------------------------
// support pinch zoom
//--------------------------------------------------------------------------
void Cube::scale(float scaleFactor) {
    myCamera->scaleModel(scaleFactor);
}

//--------------------------------------------------------------------------
// move with two finger gestures..
//--------------------------------------------------------------------------
void Cube::move(float distanceX, float distanceY) {
    myCamera->translateModel(distanceX, distanceY);
}

