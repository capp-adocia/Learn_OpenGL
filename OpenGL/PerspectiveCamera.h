#pragma once
#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fovy, float aspect, float near, float far);
    ~PerspectiveCamera();
    glm::mat4 getProjectionMatrix() override;
    void scale(float deltaScale) override;
private:
    float _fovy;
    float _aspect;
    float _near;
    float _far;
};