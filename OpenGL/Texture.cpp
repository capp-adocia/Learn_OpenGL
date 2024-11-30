#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "third/stb_image.h"

Texture::Texture(const char* path, unsigned int unit)
	: _texture(0)
	, _unit(unit)
{
    // 1 stbImage 读取图片
    stbi_set_flip_vertically_on_load(true); // 反转y轴
    stbi_uc* data = stbi_load(path, &_width, &_height, &_Channels, STBI_rgb_alpha);
    // 2 生成纹理并激活单元绑定
    glGenTextures(1, &_texture);
    // 激活纹理单元
    glActiveTexture(GL_TEXTURE0 + _unit); // 总共有32个纹理单元
    // 绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, _texture);
    // 3 传输纹理数据，开辟显存
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D); // 为当前纹理生成mipmap
    // 释放cpu端的数据
    stbi_image_free(data);

    // 4 设置纹理的过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 线性插值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); // 最近邻插值

    // 5 设置纹理的包含方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S轴指的是x轴
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T轴指的是y轴
}

Texture::~Texture()
{
    if (_texture != 0)
    {
        glDeleteTextures(1, &_texture);
    }
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE + _unit);
    glBindTexture(GL_TEXTURE_2D, _texture);
}
