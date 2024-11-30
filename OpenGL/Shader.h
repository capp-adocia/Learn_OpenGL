#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ErrorCheck.h"
// GLM 数学库
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void begin();
    void CompileAndLink();
    void end();
    inline GLuint getProgram() { return _program; }
    void setUniform1f(const char* name, float value);
    void setUniform3f(const char* name, float v1, float v2, float v3);
    void setUniform1i(const char* name, int value);
    void setUniformMat4f(const char* name, const glm::mat4& value);
private:
    GLuint _program;
    std::string _vertexCode;
    std::string _fragmentCode;
};
