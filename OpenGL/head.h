#pragma once
#include "App.h"
#include "ErrorCheck.h"
#include "Texture.h"
#include "PerspectiveCamera.h"
#include "CameraControl.h"
#include "GameCameraControl.h"
#include "TrackBallCameraControl.h"
#include "OrthographicCamera.h"

// 变换矩阵
glm::mat4 transform(1.0);
// 准备好摄像机
//glm::mat4 viewMatrix(1.0);
//glm::mat4 orthoMatrix(1.0);
//glm::mat4 perspectiveMatrix(1.0);
std::shared_ptr<OrthographicCamera> camera;
std::unique_ptr<TrackBallCameraControl> cameraControl;

void framebuffer_size_callback(int width, int height);
void keyCallBack(int key, int scancode, int action, int mods);
void prepare();
void prepareVBO();
void prepareSingleBuffer(); // 将顶点坐标和颜色坐标分别存储
void prepareInterleavedBuffer(); // 将顶点坐标和颜色坐标存储在一个数组中
//void prepareShader(); // 准备着色器
void prepareVAOForGLTriangles(); // 准备四个顶点数组对象
void prepareVAO();
void prepareTexture();
void doTransform(); // 执行变换
void prepareOrthographic(); // 准备正交投影
void preparePerspective(); // 准备透视投影

// 当窗口大小改变时，调用此函数
void framebuffer_size_callback(int width, int height);
void keyCallBack(int key, int scancode, int action, int mods);
void mouseCallBack(int button, int action, int mods);
void cursorCallBack(double xpos, double ypos);
void scrollCallBack(double offset);