#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

#define GLCHECK(func) {func; CheckErr(__FILE__, __LINE__); }
#define CHECK_SHADER(shader) {CheckSharderErr(shader, __FILE__, __LINE__); }
#define CHECK_PROGRAM(shaderProgram) {CheckProgramErr(shaderProgram, __FILE__, __LINE__); }

// 错误检查
static void CheckErr(const char* file, int line) {
    GLenum err = glGetError(); // 获取 OpenGL 错误状态
    if (err != GL_NO_ERROR) {
        std::string str;
        switch (err) {
        case GL_INVALID_ENUM: str = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE: str = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION: str = "INVALID_OPERATION"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: str = "INVALID_FRAMEBUFFER_OPERATION"; break;
        case GL_OUT_OF_MEMORY: str = "OUT_OF_MEMORY"; break;
        default: str = "Unknown Error"; break;
        }
        std::cout << "OpenGL Error at " << file << ":" << line << " - " << str << std::endl;
        std::cout << "-----------------------------" << std::endl;
        assert(false);  // 出现错误时断言失败
    }
}

static void CheckSharderErr(const GLuint shader, const char* file, int line)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Shader Compile Error at " << file << ";第" << line << "行：" << infoLog << std::endl;
        std::cout << "-----------------------------" << std::endl;
        assert(false);  // 出现错误时断言失败
    }
}

static void CheckProgramErr(const GLuint shaderProgram, const char* file, int line)
{
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader Program Link Error at " << file << ";第" << line << "行：" << infoLog << std::endl;
        std::cout << "-----------------------------" << std::endl;
        assert(false);  // 出现错误时断言失败
    }
}