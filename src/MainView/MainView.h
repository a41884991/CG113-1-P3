/* --- MainView.h --- */

/* ------------------------------------------
Author: User
Date: 10/30/2024
------------------------------------------ */

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma warning(disable:4819)

class ShaderProgram;

class MainView {
public:
    MainView();
    ~MainView();

    void Render();

private:
    ShaderProgram* program;

    GLuint VAO, VBO;
};

#endif // MAINVIEW_H
