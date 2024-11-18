#version 460

layout(location = 0) in vec3 vPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void) {
    mat4 MVP = projection * view * model;

    gl_Position = MVP * vec4(vPosition, 1.0);
}