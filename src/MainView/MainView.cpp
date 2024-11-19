/* --- MainView.cpp --- */

/* ------------------------------------------
author: User
date: 10/30/2024
------------------------------------------ */

#include "MainView.h"
#include "ShaderProgram/ShaderProgram.h"
#include "Material/Material.h"
#include "Camera/Camera.h"
#include "ControlPoint/ControlPoint.h"
#include "Track/Track.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>
#include <vector>

MainView::MainView()
{
    // Constructor
    program = new ShaderProgram("Shader/Train.vs", "Shader/Train.fs");

    material = new Material("resource/container.jpg");

    camera = new Camera();

    track = new Track();
    CreateFloor();

    viewMat = glm::mat4(1.0f);
    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    m_width = 800;
    m_height = 600;

    mouseMode = -1;
}

MainView::~MainView()
{
    // Destructor
}

void MainView::Render()
{
    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    viewMat = camera->GetViewMatrix();
    projMat = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);

    DrawFloor();

    program->Use();

    // program->SetMat4("model", model);
    program->SetMat4("view", viewMat);
    program->SetMat4("projection", projMat);

    track->Render(program);
}

void MainView::SetViewPort(int width, int height)
{
    m_width = width;
    m_height = height;

    float aspect = (float)m_width / (float)m_height;
    std::cout << aspect << std::endl;
    projMat = glm::perspective(glm::radians(80.0f), aspect, 0.1f, 100.0f);
}

void MainView::OnMouse(GLFWwindow *window, int button, int action)
{
    mouseMode = -1;

    ImGuiIO &io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        mouseMode = (action == GLFW_PRESS) ? 0 : -1;
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        mouseMode = (action == GLFW_PRESS) ? 1 : -1;
        break;
    default:
        break;
    }

    HandleMouseEvent(mouseMode, xPos, yPos);
}

void MainView::OnCursorPos(double xPos, double yPos)
{
    if (mouseMode == -1)
        return;

    HandleMouseEvent(mouseMode, xPos, yPos);
}

void MainView::HandleMouseEvent(int mode, double xPos, double yPos)
{
    static bool firstMouse = true;

    static double lastX = 0, lastY = 0;

    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    double xOffset = xPos - lastX;
    double yOffset = lastY - yPos;

    switch (mode)
    {
    case 0: // select point
        break;
    case 1: // move camera
        camera->ProcessMouseMovement(xOffset, yOffset);
        break;
    default:
        firstMouse = true;
        break;
    }

    lastX = xPos;
    lastY = yPos;
}

void MainView::CreateFloor(float size, int nSquares)
{
    floor.program = new ShaderProgram("Shader/Floor.vs", "Shader/Floor.fs");
    floor.modelMat = glm::mat4(1.0f);

    std::vector<float> floorColor1 = {.7f, .7f, .7f}; // Light color
    std::vector<float> floorColor2 = {.3f, .3f, .3f}; // Dark color

    float blockSize = size / (float)nSquares;
    float xPos = -size / 2, yPos = -size / 2;

    std::vector<float> vertices;
    int colorSelector = 0;

    for (int x = 0; x < nSquares; ++x)
    {
        yPos = -size / 2;
        for (int y = 0; y < nSquares; ++y)
        {
            auto &currentColor = (colorSelector % 2 == 0) ? floorColor1 : floorColor2;

            std::vector<float> point0 = {xPos, 0, yPos};
            std::vector<float> point1 = {xPos, 0, yPos + blockSize};
            std::vector<float> point2 = {xPos + blockSize, 0, yPos + blockSize};
            std::vector<float> point3 = {xPos + blockSize, 0, yPos};

            std::vector<float> newVertices;

            newVertices.insert(newVertices.end(), point0.begin(), point0.end());
            newVertices.insert(newVertices.end(), currentColor.begin(), currentColor.end());
            newVertices.insert(newVertices.end(), point1.begin(), point1.end());
            newVertices.insert(newVertices.end(), currentColor.begin(), currentColor.end());
            newVertices.insert(newVertices.end(), point2.begin(), point2.end());
            newVertices.insert(newVertices.end(), currentColor.begin(), currentColor.end());

            newVertices.insert(newVertices.end(), point0.begin(), point0.end());
            newVertices.insert(newVertices.end(), currentColor.begin(), currentColor.end());
            newVertices.insert(newVertices.end(), point2.begin(), point2.end());
            newVertices.insert(newVertices.end(), currentColor.begin(), currentColor.end());
            newVertices.insert(newVertices.end(), point3.begin(), point3.end());
            newVertices.insert(newVertices.end(), currentColor.begin(), currentColor.end());

            vertices.insert(vertices.end(), newVertices.begin(), newVertices.end());

            colorSelector++;
            yPos += blockSize;
        }

        xPos += blockSize;
        colorSelector++;
    }

    floor.size = vertices.size() / 6;

    glGenVertexArrays(1, &floor.VAO);
    glGenBuffers(1, &floor.VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(floor.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, floor.VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void MainView::DrawFloor()
{
    floor.program->Use();

    floor.program->SetMat4("view", viewMat);
    floor.program->SetMat4("projection", projMat);
    floor.program->SetMat4("model", floor.modelMat);

    glBindVertexArray(floor.VAO);
    glDrawArrays(GL_TRIANGLES, 0, floor.size);
}