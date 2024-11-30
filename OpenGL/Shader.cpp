#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
	: _program(0)
{
    // 读取shader文件内容
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // 读取文件内容
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件
        vShaderFile.close();
        fShaderFile.close();
        _vertexCode = vShaderStream.str();
        _fragmentCode = fShaderStream.str();
    }
    catch (const std::ifstream::failure& err)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

Shader::~Shader()
{
}

void Shader::begin()
{
	glUseProgram(_program);
}

void Shader::CompileAndLink()
{
    // 创建Shader程序(vs、fs)
    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* vertexShaderSource = _vertexCode.c_str();
    const char* fragmentShaderSource = _fragmentCode.c_str();
    // 为Shader程序分配输入shader代码
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // 编译Shader程序
    GLCHECK(glCompileShader(vertexShader));
    // 检查vertexShader程序是否编译成功
    CHECK_SHADER(vertexShader);

    GLCHECK(glCompileShader(fragmentShader));
    // 检查fragmentShader程序是否编译成功
    CHECK_SHADER(fragmentShader);
    /* 以上仅完成了Shader的编译操作，接下来完成链接操作 */
    // 创建一个Program对象壳子
    _program = glCreateProgram();
    // 将vs和fs链接到Program对象壳子中
    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fragmentShader);

    // 执行program的链接操作，形成一个完整的Shader程序
    glLinkProgram(_program);
    // 检查program是否链接成功
    CHECK_PROGRAM(_program);

    // 删除Shader程序
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::end()
{
	glUseProgram(0);
}

void Shader::setUniform1f(const char* name, float value)
{
    GLint timloc = glGetUniformLocation(getProgram(), name);
    glUniform1f(timloc, value);
}

void Shader::setUniform3f(const char* name, float v1, float v2, float v3)
{
    GLint timloc = glGetUniformLocation(getProgram(), name);
    glUniform3f(timloc, v1, v2, v3);
}

void Shader::setUniform1i(const char* name, int value)
{
    GLint location = glGetUniformLocation(getProgram(), name);
    glUniform1i(location, value);
}

void Shader::setUniformMat4f(const char* name, const glm::mat4& value)
{
    GLint location = glGetUniformLocation(getProgram(), name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr<GLfloat>(value));
}