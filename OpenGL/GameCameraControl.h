#pragma once
#include "CameraControl.h"

// 游戏控制
class GameCameraControl : public CameraControl
{
public:
	GameCameraControl(std::shared_ptr<Camera> camera);
	~GameCameraControl();

	void update() override;
	void onCursor(float x, float y) override;

	inline void setSpeed(float speed) {_speed = speed;}

private:
	void pitch(float angle); // 俯仰
	void yaw(float angle); // 偏航
	float _speed = 0.001f;
	float _TranslateSpeed = 0.1f; // 平移速度
	float _pitch{ 0.1f }; // 俯仰值
};
