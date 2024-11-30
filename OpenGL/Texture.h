#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture
{
public:
    Texture(const char* path, unsigned int unit);
    ~Texture();

    void bind(); // 对当前纹理单元进行再次绑定
private:
    GLuint _texture;
    int _width, _height, _Channels;
    unsigned int _unit;
};
