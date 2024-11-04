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
    static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
    void ProcessInput(GLFWwindow *window);

    void SetWidth(int width);
    void SetHeight(int height);

private:
    unsigned int width;
    unsigned int height;

    GLFWwindow *window;
    ControlWindow *controlWindow;

    MainView *view;

    // static MainWindow *instance;
};
