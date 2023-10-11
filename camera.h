#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera{

public:
    glm::vec4 forward;
    glm::vec4 right;
    glm::vec4 up;
    float fieldofView;
    glm::vec4 cameraposition;
    float nearclip;
    float farclip;
    float aspectratio;

    Camera();

    glm::mat4 returnViewMatrix();
    glm::mat4 returnProjectionMatrix();

    void translateforward(float t);
    void translateright(float t);
    void translateup(float t);
    void rotatecamx(float x);
    void rotatecamy(float y);
    void rotatecamz(float z);

    glm::vec4 dir();

};
