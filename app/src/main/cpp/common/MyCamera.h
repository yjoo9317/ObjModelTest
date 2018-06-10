//
// Created by Youngjoo Park on 6/6/18.
//

#ifndef NATIVETEST_MYCAMERA_H
#define NATIVETEST_MYCAMERA_H

// Translation Matrix : identity matrix with additional elements at the last column
/*------------------------
    1 0 0 x (x translation)
    0 1 0 y (y translation)
    0 0 1 z (z translation)
    0 0 0 1
 ---------------------------*/
// coefficients for translating gestures to model's movement

#include <vector>
#include <simpleGLM.h>

#define SCALE_TO_Z_TRANSLATION 20
#define TRANSLATION_TO_ANGLE 5
#define XY_TRANSLATION_FACTOR 10

class MyCamera {
public:
    MyCamera (float fov = 45, float zPosit = 10, float near= 1.0f, float far = 2000.0f);
    void setModelPosition(std::vector<float> modelPosition);
    void setAspectRatio(float aspect);
    glm::mat4 getMVP() { return mvpMatrix; }
    void rotateModel(float distanceX, float distanceY, float endX, float endY);
    void scaleModel(float scaleFactor);
    void translateModel(float distanceX, float distanceY);

private:
    void computeMVPMatrix();

    float fov;
    float nearPlane, farPlane;

    //---------------------------------------------------------------------------------------
    // MVP(ModelView Projection) Matrix = ProjectMatrix X ModelMatrix X Vertex (model)
    //---------------------------------------------------------------------------------------

    glm::mat4 projectionViewMatrix;
    glm::mat4 rotateMatrix;
    glm::mat4 translateMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 mvpMatrix;

    ///---------------------------------------------------------------------------------------
    // Don't know what it means????
    // six degree of freedom of the model contained in a quaternion and x,y,z coordinates
    //---------------------------------------------------------------------------------------
    glm::quat modelQuaternion;
    float deltaX, deltaY, deltaZ;
};


#endif //NATIVETEST_MYCAMERA_H
