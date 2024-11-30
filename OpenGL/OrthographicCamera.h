#pragma once
#include "Camera.h"

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(float left, float right, float top, float bottom, float near, float far);
    ~OrthographicCamera();
    glm::mat4 getProjectionMatrix() override;
    void scale(float deltaScale) override;
private:
    float _left;
    float _right;
    float _top;
    float _bottom;
    float _near;
    float _far;
    float _scale{ 0.0f };
};