#include "GameCameraControl.h"

GameCameraControl::GameCameraControl(std::shared_ptr<Camera> camera)
	: CameraControl(camera)
{
}

GameCameraControl::~GameCameraControl()
{
}

void GameCameraControl::onCursor(float x, float y)
{
	float deltaX = (x - _currentX) * _sensitivity;
	float deltaY = (y - _currentY) * _sensitivity;
	if (_rightMouseDown)
	{
		pitch(deltaY);
		yaw(deltaX);
	}
	_currentX = x;
	_currentY = y;
}

// 这个用来更新键盘按键按下后的操作
void GameCameraControl::update()
{
	glm::vec3 direction(0.0f);
	if (_keysMap[GLFW_KEY_W])
	{
		direction += _camera->getFront();
	}
	if (_keysMap[GLFW_KEY_S])
	{
        direction -= _camera->getFront();
	}
	if (_keysMap[GLFW_KEY_A])
	{
		direction -= _camera->getRight();
	}
	if (_keysMap[GLFW_KEY_D])
	{
		direction += _camera->getRight();
	}
	if (glm::length(direction) != 0)
	{
		direction = glm::normalize(direction);
		_camera->setPosition(_camera->getPosition() + direction * _speed);
	}
	
}

void GameCameraControl::pitch(float angle)
{
	_pitch += angle;
	if (_pitch > 89.0f || _pitch < -89.0f)
	{
		_pitch -= angle;
		return;
	}
	glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), _camera->getRight());
	_camera->setUp(mat * glm::vec4(_camera->getUp(), 0.0f));
}

void GameCameraControl::yaw(float angle)
{
	glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	// 改变了up向量和right向量，共同影响了摄像机朝向向量
	// 也就是说，这种旋转类似于
	_camera->setUp(mat * glm::vec4(_camera->getUp(), 0.0f));
	_camera->setRight(mat * glm::vec4(_camera->getRight(), 0.0f));
}
