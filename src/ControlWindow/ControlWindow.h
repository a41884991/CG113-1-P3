#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "DataStructure.h"

#pragma warning(disable : 4819)

class ControlWindow
{
public:
    ControlWindow(GLFWwindow *window);

    ~ControlWindow();

    void Render();

    const ControlData &GetControlData() const { return m_controlData; };

private:
    bool showDemoWindow;
    ControlData m_controlData;
    float trainSpeed;

    bool isTrainTimeDisabled;
};