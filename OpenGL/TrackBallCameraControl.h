#pragma once
#include "CameraControl.h"

class TrackBallCameraControl : public CameraControl
{
public:
	TrackBallCameraControl(std::shared_ptr<Camera> camera);
	~TrackBallCameraControl();
	void update() override;
	void onCursor(float x, float y) override;
	void onScroll(float offset) override;
private:
	void pitch(float angle); // 俯仰
	void yaw(float angle);

	float _TranslateSpeed = 0.01f; // 平移速度
};