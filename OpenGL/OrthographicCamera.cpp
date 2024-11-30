#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float near, float far)
    : _left(left)
    , _right(right)
    , _top(top)
    , _bottom(bottom)
    , _near(near)
    , _far(far)
{
}

OrthographicCamera::~OrthographicCamera()
{
}

glm::mat4 OrthographicCamera::getProjectionMatrix()
{
    float scale = std::pow(2.0f, _scale);
    return glm::ortho(_left * scale, _right * scale, _bottom * scale, _top * scale, _near, _far);
}

void OrthographicCamera::scale(float deltaScale)
{
    _scale += deltaScale;
}
