/* --- ShaderProgram.h --- */

/* ------------------------------------------
Author: User
Date: 10/30/2024
------------------------------------------ */

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderProgram {
public:
    ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~ShaderProgram();

    void Use();

private:
    GLuint ID;

};

#endif // SHADERPROGRAM_H
