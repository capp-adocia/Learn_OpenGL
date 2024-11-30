#version 460 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 uv; // 经过了插值后de的纹理坐标

uniform sampler2D huoyinSample;

void main() {
    // 使用纹理坐标采样纹理
    vec4 huoyinColor = texture(huoyinSample, uv);
    FragColor = vec4(huoyinColor.rgb, 1.0);
}