#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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

private:
    int width;
    int height;

    GLFWwindow *window;
    ControlWindow *controlWindow;

    MainView *view;

    // static MainWindow *instance;
};
