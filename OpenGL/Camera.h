#pragma once
#include "pch.h"

// 相机父类，子类有透视投影相机和正交投影相机
class Camera
{
public:
	Camera();
    virtual ~Camera();
	glm::mat4 getViewMatrix(); // 获取相机的视图矩阵
	virtual glm::mat4 getProjectionMatrix(); // 获取相机的投影矩阵
	inline glm::vec3 getPosition() const { return _Position; }
	inline glm::vec3 getUp() const { return _Up; }
	inline glm::vec3 getRight() const { return _Right; }
	inline glm::vec3 getFront() const { return _Front; }

	inline void setPosition(glm::vec3 position) { _Position = position; }
	inline void setUp(glm::vec3 up) { _Up = up; }
	/*inline void setFront(glm::vec3 front) { _Front = front; } 不需要*/
	inline void setRight(glm::vec3 right) { _Right = right; }
	virtual void scale(float deltaScale = 0) = 0;
protected:
	glm::vec3 _Position;
	glm::vec3 _Up; // 脑袋的上方
	glm::vec3 _Right;

    glm::vec3 _Front; // 前方
};
