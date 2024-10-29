#pragma once

#pragma warning(push)
#pragma warning(disable : 4312)
#pragma warning(disable : 4311)
#pragma warning(pop)

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>

class ControlWindow
{
public:
    ControlWindow(const bool showDemoWindow = true);

    ~ControlWindow();

    void Initialize(GLFWwindow* window);

    void Render();

private:
    bool showDemoWindow;
};