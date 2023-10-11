#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "camera.h"

Camera::Camera() : forward(glm::vec4(0, 0, -1, 0)), right(glm::vec4(1, 0, 0, 0)),
    up(glm::vec4(0,1,0,0)), fieldofView(45), cameraposition(glm::vec4(0, 0, 10, 1)),
    nearclip(0.01), farclip(100.f), aspectratio(1.f) {}


glm::mat4 Camera::returnViewMatrix(){
    glm::mat4 translateView(1,0,0,0,
                            0,1,0,0,
                            0,0,1,0,
                            -cameraposition[0], -cameraposition[1], -cameraposition[2], 1);

    glm::mat4 orientView(-1* right[0], up[0], forward[0], 0,
                        right[1], -1*up[1], forward[1], 0,
                        right[2], up[2], forward[2], 0,
                          0,0,0,1);

    return orientView*translateView;
}

glm::mat4 Camera::returnProjectionMatrix() {
    float p = farclip/(farclip-nearclip);
    float q = -farclip * nearclip/(farclip-nearclip);
    float s = 1/ tan(fieldofView/2);

    return glm::mat4(glm::vec4(s/aspectratio, 0, 0, 0),
                     glm::vec4(0,s,0,0),
                     glm::vec4(0,0,p,1),
                     glm::vec4(0,0,q,0));

}



void Camera::translateforward(float t){
    glm::vec4 translate = forward * t;
    cameraposition += translate;
}


void Camera::translateright(float t){
    glm::vec4 translate = right * t;
    cameraposition += translate;
}

void Camera::translateup(float t){
    glm::vec4 translate = up * t;
    cameraposition += translate;
}

void Camera::rotatecamx(float x){
    glm::mat4 rot(1.0f);
    rot = glm::rotate(rot, x, glm::vec3(right[0], right[1], right[2]));
    forward = rot * forward;
    up = rot * up;
}

void Camera::rotatecamy(float y){
    glm::mat4 rot(1.0f);
    rot = glm::rotate(rot, y, glm::vec3(up[0], up[1], up[2]));
    right = rot * right;
    forward = rot * forward;
}
void Camera::rotatecamz(float z){
    glm::mat4 rot(1.0f);
    rot = glm::rotate(rot, z, glm::vec3(forward[0], forward[1], forward[2]));
    right = rot * right;
    up = rot * up;
}

glm::vec4 Camera::dir(){
    return forward;
}
