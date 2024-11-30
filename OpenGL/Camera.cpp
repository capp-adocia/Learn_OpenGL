#include "Camera.h"

Camera::Camera()
	: _Position(glm::vec3(0.0f, 0.0f, 1.0f))
	, _Up(glm::vec3(0.0f, 1.0f, 0.0f))
	, _Right(glm::vec3(1.0f, 0.0f, 0.0f))
{
	_Front = glm::cross(_Up, _Right); // 保证前向向量方向正确
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	_Front = glm::cross(_Up, _Right);
	return glm::lookAt(_Position, _Position + _Front, _Up);
}

glm::mat4 Camera::getProjectionMatrix() // 让子类实现
{
	return glm::identity<glm::mat4>();
}