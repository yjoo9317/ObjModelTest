//
// Created by Youngjoo Park on 6/6/18.
//

#include "MyCamera.h"
#include "myLogger.h"
#include "math.h"

MyCamera::MyCamera(float fov, float zPosit, float near, float far) {
    glm::vec3 cameraPosition = glm::vec3(0, 0, zPosit);

    viewMatrix = glm::lookAt(cameraPosition,/* eye */ glm::vec3(0, 0, -1), /* pointing up */glm::vec3(0, 1, 0));
    this->nearPlane = near;
    this->farPlane = far;
    this->fov = fov;  // Field of Vision (angle toward frustrum )

    deltaX = deltaY = deltaZ = 0;
    modelQuaternion = glm::quat(glm::vec3(0,0,0));

    modelMatrix = glm::mat4(1.0f);
    translateMatrix = glm::mat4(1.0f);
    rotateMatrix = glm::mat4(1.0f);
    mvpMatrix = glm::mat4(1.0f); // initialized as identity matrix
}

void MyCamera::setAspectRatio(float aspect) {

    glm::mat4 projectionMatrix;

    // setting up projection matrix
    //--------------------------------------------------------
    //  (a / aspect) 0        0           0
    //       0       a        0           0
    //       0       0  -(f+n)/(f-n)   - 2*f*n/f-n
    //       0       0       -1           0
    //--------------------------------------------------------
    projectionMatrix = glm::perspective(fov*float(M_PI / 180), // camera view
                                        aspect,                // camera aspect ratio
                                        nearPlane,             // distance to near plane
                                        farPlane);             // distance to far plane

    projectionViewMatrix = projectionMatrix * viewMatrix;
    computeMVPMatrix();

}

void MyCamera::computeMVPMatrix() {

    translateMatrix = glm::mat4 (1, 0, 0, 0,                 // column 0
                                 0, 1, 0, 0,                 // column 1
                                 0, 0, 1, 0,                 // column 2
                                 deltaX, deltaY, deltaZ, 1); // column 3 with translation elements

    // vertex for clip = ProjectionMatrix * ModelMatrix * vertex model
    modelMatrix = translateMatrix * rotateMatrix;
    mvpMatrix = projectionViewMatrix * modelMatrix;
}

void MyCamera::setModelPosition(std::vector<float> modelPosition) {
    deltaX = modelPosition[0];
    deltaY = modelPosition[1];
    deltaZ = modelPosition[2];

    // The angles of rotation
    float pitchAngle = modelPosition[3];
    float yawAngle = modelPosition[4];
    float rollAngle = modelPosition[5];

    // quaternion : rotation by an angle around an axis in the 3D space
    // The angles of rotation converted to quaternion
    modelQuaternion = glm::quat(glm::vec3(pitchAngle, yawAngle, rollAngle));
    //-------------------------------------------------------------------------
    // model quaternion converted to 4X4 matrix => Rotation matrix
    rotateMatrix = glm::toMat4(modelQuaternion);
    //--------------------------------------------------------------------------
    computeMVPMatrix();
}

void MyCamera::rotateModel(float distanceX, float distanceY, float endX, float endY) {

    // ending vector
    float dist = sqrt(fmin(1, endX * endX + endY * endY));
    float positionZ = sqrt(1 - dist*dist);
    glm::vec3 endVec = glm::vec3(endX, endY, positionZ);
    endVec = glm::normalize(endVec);

    // starting vector
    endX += distanceX;
    endY += distanceY;
    dist = sqrt(fmin(1, endX * endX + endY * endY));
    positionZ = sqrt(1 - dist * dist);
    glm::vec3 beginVec = glm::vec3(endX, endY, positionZ);
    beginVec = glm::normalize(beginVec);

    // perform a cross product of vectors to get axis of rotation
    glm::vec3 rotationAxis = glm::cross(beginVec, endVec);
    rotationAxis = glm::normalize(rotationAxis);

    float dotProduct = fmax(fmin(glm::dot(beginVec, endVec), 1.), -1.);
    float rotationAngle = TRANSLATION_TO_ANGLE * acos(dotProduct);

    // update quaternion and rotation matrix
    modelQuaternion = glm::angleAxis(rotationAngle, rotationAxis);
    rotateMatrix = glm::toMat4(modelQuaternion) * rotateMatrix;
    computeMVPMatrix();
}

void MyCamera::scaleModel(float scaleFactor) {
    deltaZ += SCALE_TO_Z_TRANSLATION * (scaleFactor -1);
    computeMVPMatrix();
}

void MyCamera::translateModel(float distanceX, float distanceY) {
    deltaX += XY_TRANSLATION_FACTOR * distanceX;
    deltaY += XY_TRANSLATION_FACTOR * distanceY;
    computeMVPMatrix();
}