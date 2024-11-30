#pragma once
#include "pch.h"
#include <unordered_map>
#include "Camera.h"
#include <memory>
#include <iostream>
#include "App.h"

class CameraControl
{
public:
    CameraControl() = default;
    CameraControl(std::shared_ptr<Camera> camera);
    virtual ~CameraControl();
    virtual void update(); // 每一帧更新相机的位置
    virtual void onMouse(int button, int action, int x, int y);
    virtual void onCursor(float x, float y);
    virtual void onKey(int key, int action, int mods); // 用上下左右键来控制相机
    virtual void onScroll(float offset);

    inline void setCamera(std::shared_ptr<Camera> camera) { _camera = camera; }
    inline void setSensitivity(float sensitivity) { _sensitivity = sensitivity; }
    inline void setScaleSpeed(float scaleSpeed) { _scaleSpeed = scaleSpeed; }
protected:
    bool _leftMouseDown = false;
    bool _rightMouseDown = false;
    bool _middleMouseDown = false;

    float _currentX = 0.0f;
    float _currentY = 0.0f;
    float _sensitivity = 0.2f; // 灵敏度
    std::unordered_map<int, bool> _keysMap;
    std::shared_ptr<Camera> _camera = nullptr;
    float _scaleSpeed = 0.2f;
};
