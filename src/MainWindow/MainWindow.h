#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "DataStructure.h"

class ControlWindow;
class MainView;
class MainWindow
{
public:
    MainWindow(const unsigned int width = 800, const unsigned int height = 600);

    void Initialize();

    void Show();

    void CreateView();

private:
    void ProcessInput(GLFWwindow *window);
    void BindCallBack();
    void HandleControlData(const ControlData &controlData);

private:
    int width;
    int height;

    float deltaTime = 0.0f; // time between current frame and last frame
    float lastFrame = 0.0f;

    GLFWwindow *window;
    ControlWindow *controlWindow;

    MainView *view;

    // static MainWindow *instance;
};
