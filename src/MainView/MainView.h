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

#include "DataStructure.h"

#pragma warning(disable : 4819)

class ShaderProgram;
class Material;
class Camera;
class ControlPoint;
class Track;
class Model;

class MainView
{
public:
    MainView();
    ~MainView();

    void Render();

    void SetViewPort(int width, int height);
    void OnMouse(GLFWwindow *window, int button, int action);
    void OnCursorPos(double xPos, double yPos);
    void OnKey(int key, float deltaTime);
    void OnControlData(const ControlData &controlData);
    void HandleMouseEvent(int mode, double xPos, double yPos);

private:
    void CreateFloor(float size = 8, int nSquares = 10);
    void createIDTexture();
    void DrawFloor();
    int getID(const int mouseX, const int mouseY);
    glm::vec3 getWorldPos(const int mouseX, const int mouseY);

private:
    struct Floor
    {
        int size;
        GLuint VAO, VBO;
        ShaderProgram *program;
        glm::mat4 modelMat;
    };

    struct IDTexture
    {
        GLuint texture;
        GLuint FBO;
    };

    ShaderProgram *program;
    ShaderProgram *idProgram;
    ShaderProgram *modelProgram;

    Camera *camera;

    Track *track;

    glm::mat4 projMat;
    glm::mat4 viewMat;

    Floor floor;
    IDTexture idTexture;

    Model *test;

    int m_width, m_height;

    int mouseMode;
};

#endif // MAINVIEW_H
