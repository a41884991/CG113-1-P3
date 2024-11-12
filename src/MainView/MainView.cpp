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

#include <iostream>

MainView::MainView()
{
    // Constructor
    program = new ShaderProgram("Shader/Train.vs", "Shader/Train.fs");
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // 左上
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
    };

    material = new Material("resource/container.jpg");

    camera = new Camera();

    point = new ControlPoint(glm::vec3(0.0f, 0.0f, 0.0f), 0);
}

MainView::~MainView()
{
    // Destructor
}

void MainView::Render()
{
    program->Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    view = camera->GetViewMatrix();

    // glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // program->SetMat4("model", model);
    program->SetMat4("view", view);
    program->SetMat4("projection", projection);

    point->Render(program);
}