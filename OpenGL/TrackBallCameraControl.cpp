#include "TrackBallCameraControl.h"

TrackBallCameraControl::TrackBallCameraControl(std::shared_ptr<Camera> camera)
	: CameraControl(camera)
{
}

TrackBallCameraControl::~TrackBallCameraControl()
{
}

void TrackBallCameraControl::update()
{

}

void TrackBallCameraControl::onCursor(float x, float y)
{
	if (_leftMouseDown)
	{
		// 计算经线和纬线旋转的增量角度
		float deltaX = (x - _currentX) * _sensitivity;
		float deltaY = (y - _currentY) * _sensitivity;
		pitch(deltaY);
		yaw(deltaX);
	}
	else if (_middleMouseDown)
	{
		// 中键按住平移
		float deltaX = (_currentX - x) * _TranslateSpeed;
		float deltaY = (_currentY - y) * _TranslateSpeed;
		glm::vec3 cameraPos = _camera->getPosition();
		glm::vec3 cameraUp = _camera->getUp();
		glm::vec3 cameraRi = _camera->getRight();
		// 同时更新 X 和 Y 坐标
		//_camera->setPosition(glm::vec3(cameraPos.x, cameraPos.y += deltaY, cameraPos.z));
		//_camera->setPosition(glm::vec3(cameraPos.x += deltaX, cameraPos.y, cameraPos.z));

		_camera->setPosition(glm::vec3(cameraPos += cameraUp * deltaY));
		_camera->setPosition(glm::vec3(cameraPos += cameraRi * deltaX));
	}
	_currentX = x;
	_currentY = y;
}

// 鼠标上下移动时，图片上下旋转
void TrackBallCameraControl::pitch(float angle)
{
	// 围绕right向量旋转
	glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), _camera->getRight());

	// 影响当前相机的up向量和位置
	_camera->setUp(mat * glm::vec4(_camera->getUp(), 0.0f)); // 旋转up向量 产生一个4*4的旋转矩阵,这里舍去了第四个分量
	_camera->setPosition(mat * glm::vec4(_camera->getPosition(), 1.0f));
}

// 鼠标左右移动时，图片左右旋转
void TrackBallCameraControl::yaw(float angle)
{
	// 围绕着y轴旋转
	// up向量不变，只需要旋转right和setPosition位置
	glm::mat4 mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), _camera->getUp());
	// 这里必须改变right向量，如果改变了front向量的话，等于没改，因为后续front向量是right和up叉乘得到的
	// 所以这里只需要改变right向量即可
	_camera->setRight(mat * glm::vec4(_camera->getRight(), 0.0f));
	_camera->setPosition(mat * glm::vec4(_camera->getPosition(), 1.0f));
}

void TrackBallCameraControl::onScroll(float offset)
{
	_camera->scale(_scaleSpeed * offset);
}