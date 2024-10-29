

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "MainWindow/MainWindow.h"

void InitializeGLFW();
void InitializeGLAD();

int main()
{
    InitializeGLFW();

    MainWindow mainWindow;

    try
    {
        mainWindow.Initialize();
        InitializeGLAD();
    }
    catch (const char *message)
    {
        std::cout << message << std::endl;
        glfwTerminate();
        return -1;
    }

    mainWindow.Show();

    return 0;
}

void InitializeGLFW()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void InitializeGLAD()
{
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw "Failed to initialize GLAD";
}
