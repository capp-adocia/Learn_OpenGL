#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far)
	: _fovy(fovy)
	, _aspect(aspect)
	, _near(near)
	, _far(far)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

glm::mat4 PerspectiveCamera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(_fovy), _aspect, _near, _far);
}

void PerspectiveCamera::scale(float deltaScale)
{
	glm::vec3 front = glm::cross(_Up, _Right);
	_Position += (front * deltaScale);
}
