#include "CameraControl.h"

CameraControl::CameraControl(std::shared_ptr<Camera> camera)
	: _camera(camera)
{
}

CameraControl::~CameraControl()
{
}

void CameraControl::update() // 子类实现
{
}

void CameraControl::onMouse(int button, int action, int x, int y)
{
    // 是否按下
    bool pressed = (action == GLFW_PRESS);

    // 如果按下鼠标，记录当前位置
    if (pressed)
    {
        _currentX = x;
        _currentY = y;
    }

    // 根据按下的鼠标按键不同来更改按键状态
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        _leftMouseDown = pressed;
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        _rightMouseDown = pressed;
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        _middleMouseDown = pressed;
        break;
    default:
        break;
    }
}

void CameraControl::onCursor(float x, float y)
{
    _currentX = x;
    _currentY = y;
}

void CameraControl::onKey(int key, int action, int mods)
{
    // 过滤掉重复的情况
    if (action == GLFW_REPEAT)
    {
        return;
    }
    bool pressed = (action == GLFW_PRESS);
    _keysMap[key] = pressed;
}

void CameraControl::onScroll(float offset)
{

}
