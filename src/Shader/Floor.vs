#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 v_Color;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model* vec4(aPos, 1.0));
    v_Color = aColor;
    Normal = vec3(0,1,0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

