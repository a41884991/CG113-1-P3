#include "MainWindow.h"
#include "ControlWindow/ControlWindow.h"
#include "MainView/MainView.h"

#include <iostream>

MainWindow::MainWindow(const unsigned int width, const unsigned int height)
    : width(width), height(height)
{
    // instance = this;
}

void MainWindow::Initialize()
{
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(width, height, "RollerCoasters", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    controlWindow = new ControlWindow(window);
}

void MainWindow::Show()
{
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        // input
        // -----
        ProcessInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view->Render();
        controlWindow->Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    controlWindow->~ControlWindow();
    glfwTerminate();
}

void MainWindow::CreateView()
{
    view = new MainView();
    glEnable(GL_DEPTH_TEST);
}

void MainWindow::BindCallBack()
{

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow *window, int w, int h)
        {
            auto mainWindow = static_cast<MainWindow *>(glfwGetWindowUserPointer(window));
            mainWindow->view->SetViewPort(w, h);
        });
    glfwSetMouseButtonCallback(
        window,
        [](GLFWwindow *window, int button, int action, int mods)
        {
            auto mainWindow = static_cast<MainWindow *>(glfwGetWindowUserPointer(window));
            mainWindow->view->OnMouse(window, button, action);
        });

    glfwSetCursorPosCallback(
        window,
        [](GLFWwindow *window, double xPos, double yPos)
        {
            auto mainWindow = static_cast<MainWindow *>(glfwGetWindowUserPointer(window));
            mainWindow->view->OnCursorPos(xPos, yPos);
        });
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void MainWindow::ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}