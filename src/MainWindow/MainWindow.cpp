#include "MainWindow.h"
#include "ControlWindow/ControlWindow.h"
#include "MainView/MainView.h"

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
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void MainWindow::ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void MainWindow::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void MainWindow::SetWidth(int width)
{
    this->width = width;
}

void MainWindow::SetHeight(int height)
{
    this->height = height;
}