#include <vld.h>
#include "head.h"

void framebuffer_size_callback(int width, int height)
{
    std::cout << "framebuffer_size_callback" << std::endl;
}
void keyCallBack(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(AppInstance.getWindow(), true); // 按下 ESC 键，关闭窗口
    cameraControl->onKey(key, action, mods);
}
void mouseCallBack(int button, int action, int mods)
{
    double x, y;
    AppInstance.getCursorPosition(&x, &y); // 获取当前鼠标位置
    cameraControl->onMouse(button, action, x, y);
}
void cursorCallBack(double xpos, double ypos)
{
    cameraControl->onCursor(xpos, ypos);
}
void scrollCallBack(double offset)
{
    cameraControl->onScroll(offset);
}

void prepare()
{
    // 1. 创建一个VBO
    GLuint vbo = 0;
    GLCHECK(glGenBuffers(1, &vbo));
    // 2. 销毁一个VBO
    GLCHECK(glDeleteBuffers(1, &vbo));
    // 3. 创建n个VBO
    GLuint vboArr[] = { 0,0,0 };
    GLCHECK(glGenBuffers(3, vboArr));
    //std::cout << "vboArr[0] = " << vboArr[0] << "; vboArr[1] = " << vboArr[1] << "; vboArr[2] = " << vboArr[2] << std::endl;
    // 4. 销毁n个VBO
    GLCHECK(glDeleteBuffers(3, vboArr));
}
void prepareVBO()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // left
         0.5f, -0.5f, 0.0f,  // right
         0.0f,  0.5f, 0.0f   // top
    };
    // 1、生成一个VBO
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    // 2、绑定当前vbo，到opengl状态机的当前vbo插槽上
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // 3、将数据拷贝到当前绑定的vbo上
    GLCHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

}
void prepareSingleBuffer()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // left
         0.5f, -0.5f, 0.0f,  // right
         0.0f,  0.5f, 0.0f   // top
    };
    float colors[] = {
        1.0f, 0.0f, 0.0f,  // left
        0.0f, 1.0f, 0.0f,  // right
        0.0f, 0.0f, 1.0f   // top
    };
    // 1、生成两个VBO
    GLuint verticeVBO = 0;
    GLuint colorVBO = 0;
    glGenBuffers(1, &verticeVBO);
    glGenBuffers(1, &colorVBO);

    glBindBuffer(GL_ARRAY_BUFFER, verticeVBO);
    GLCHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    GLCHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    GLuint vao = 0;
    glGenVertexArrays(1, &vao); // 生成一个VAO
    glBindVertexArray(vao); // 绑定VAO
    // 先绑定顶点数据，glVertexAttribPointer才知道从哪里读取顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, verticeVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glBindVertexArray(0); // 解绑VAO
}
void prepareInterleavedBuffer()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLCHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    //GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); // 先绑定指定的VAO
    // 先绑定顶点坐标，glVertexAttribPointer才知道从哪里读取顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // 顶点坐标数据
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // 再绑定顶点颜色数据
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0); // 解绑VAO，防止后续操作影响当前VAO

}
void prepareVAOForGLTriangles()
{
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };
    GLuint posvbo;
    glGenBuffers(1, &posvbo);
    glBindBuffer(GL_ARRAY_BUFFER, posvbo);
    GLCHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    // 生成VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // 绑定顶点坐标数据
    glBindBuffer(GL_ARRAY_BUFFER, posvbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glBindVertexArray(0); // 解绑VAO
}
void prepareVAO()
{
    //float positions[] = {
    //    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    //     0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    //     0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    //     0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 0.5f,
    //};
    float positions[] = {
        -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
        //2, 1, 3
    };
    float uvs[] = {
        0.0f, 0.0f,
        0.5f, 1.0f,
        1.0f, 0.0f,
        //1.0f, 1.0f
    };

    // 创建位置VBO
    GLuint posvbo = 0, indvbo = 0, uvvbo = 0;
    glGenBuffers(1, &posvbo);
    glBindBuffer(GL_ARRAY_BUFFER, posvbo);
    GLCHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
    // 创建EBO
    glGenBuffers(1, &indvbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indvbo);
    GLCHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    // 创建UVVBO
    glGenBuffers(1, &uvvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvvbo);
    GLCHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW));
    // VAO创建
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 动态获取位置
    GLuint posLocation = glGetAttribLocation(shader.getProgram(), "aPos"); // 0
    GLuint colorLocation = glGetAttribLocation(shader.getProgram(), "aColor"); // 1
    GLuint uvLocation = glGetAttribLocation(shader.getProgram(), "aUV"); // 2
    // 绑定VBO EBO 加入属性描述信息
    // pos color VBO
    glBindBuffer(GL_ARRAY_BUFFER, posvbo);
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indvbo);
    // UV VBO
    glBindBuffer(GL_ARRAY_BUFFER, uvvbo);
    glEnableVertexAttribArray(uvLocation);
    glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindVertexArray(0); // 解绑VAO
}
void prepareTexture()
{
    // 已封装到Texture类中
}
void doTransform()
{
    double curT = glfwGetTime();  // 获取当前时间
    float rotate = float(curT * 45.0f); // 计算旋转角度
    // 构建一个旋转矩阵，绕着z轴旋转45度角
    transform = glm::rotate(glm::mat4(1.0f), glm::radians(rotate), glm::vec3(0.0, 0.0, 1.0));
    // 平移变换
    //transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 1.0));
    // 缩放变换
    //transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 1.0));
}
void prepareCamera()
{
    // lookAt函数：生成一个viewMatrix
    // 参数1：摄像机位置
    // 参数2：摄像机目标位置
    // 参数3：摄像机的上方向
    //viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    float size = 2.0f;
    //camera = std::make_shared<PerspectiveCamera>(90.0f, (float)AppInstance.getWidth() / (float)AppInstance.getHeight(), 0.1f, 1000.0f);
    camera = std::make_shared<OrthographicCamera>(-size, size, size, -size, size, -size);
    cameraControl = std::make_unique<TrackBallCameraControl>(camera);
}
void prepareOrthographic()
{
    // 正交投影矩阵
    //orthoMatrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f);
}
void preparePerspective()
{
    //perspectiveMatrix = glm::perspective(glm::radians(90.0f), (float)AppInstance.getWidth() / (float)AppInstance.getHeight(), 0.1f, 1000.0f);
}

int main() {
    AppInstance.init(800, 600, "LearnOpenGL");

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    AppInstance.setResizeCallBack(framebuffer_size_callback);
    AppInstance.setKeyCallBack(keyCallBack);
    AppInstance.setMouseCallBack(mouseCallBack);
    AppInstance.setCursorCallBack(cursorCallBack);
    AppInstance.setScrollCallBack(scrollCallBack);

    //prepare(); // 准备渲染数据
    //prepareVBO();
    //prepareSingleBuffer();

    //prepareShader();
    // 先对shader进行编译和链接
    shader.CompileAndLink();
    // 准备VAO
    prepareVAO();
    //prepareTexture();
    Texture huoyinTexture("huoyin.jpg", 0);
    //doTransform(); // 变换
    prepareCamera();
    //prepareOrthographic();
    preparePerspective();
    
    while (AppInstance.update())
    {
        /* 清屏 */
        glClear(GL_COLOR_BUFFER_BIT);
        /* 渲染操作 */
        glBindVertexArray(vao);
        shader.begin();
        // 设置每一帧的uniform值
        shader.setUniform1f("time", glfwGetTime());
        shader.setUniform1i("huoyinSample", 0);
        shader.setUniformMat4f("transform", transform);

        shader.setUniformMat4f("viewMatrix", camera->getViewMatrix());
        shader.setUniformMat4f("projectionMatrix", camera->getProjectionMatrix());
        cameraControl->update();
        // 使用EBO复用顶点数据
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        shader.end();
        glBindVertexArray(0);
    }

    AppInstance.destroy();
    return 0;
}