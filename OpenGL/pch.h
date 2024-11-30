#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// GLM 数学库
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>
#include "Shader.h"

static GLuint vao = 0;
static Shader shader("vertex.glsl", "fragment.glsl");