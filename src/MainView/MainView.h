/* --- MainView.h --- */

/* ------------------------------------------
Author: User
Date: 10/30/2024
------------------------------------------ */

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#pragma warning(disable:4819)

class ShaderProgram;
class Material;
class Camera;
class ControlPoint;

class MainView {
public:
    MainView();
    ~MainView();

    void Render();

private:
    ShaderProgram* program;

    GLuint VAO, VBO;

    Material* material;

    Camera* camera;

    ControlPoint* point;
};

#endif // MAINVIEW_H
