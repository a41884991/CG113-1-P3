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
#include <glm/glm.hpp>

#pragma warning(disable : 4819)

class ShaderProgram;
class Material;
class Camera;
class ControlPoint;

class MainView
{
public:
    MainView();
    ~MainView();

    void Render();

    void SetViewPort(int& width, int& height);

private:
    struct Floor
    {
        int size;
        GLuint VAO, VBO;
        ShaderProgram *program;
        glm::mat4 modelMat;
    };
    
    ShaderProgram *program;

    Material *material;

    Camera *camera;

    ControlPoint *point;

    glm::mat4 projMat;
    glm::mat4 viewMat;

    Floor floor;

    int m_width, m_height;

    void CreateFloor(float size = 8, int nSquares = 10);
    void DrawFloor();
};

#endif // MAINVIEW_H
