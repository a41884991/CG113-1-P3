#pragma once

#pragma warning(push)
#pragma warning(disable : 4312)
#pragma warning(disable : 4311)
#pragma warning(pop)

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class ControlWindow;
class MainWindow
{
public:
    MainWindow(const unsigned int width = 800, const unsigned int height = 600);

    void Initialize();

    void Show();

private:
    static void FramebufferSizeCallback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }
    void ProcessInput(GLFWwindow *window);

private:
    unsigned int width;
    unsigned int height;

    GLFWwindow *window;
    ControlWindow* controlWindow;
};
