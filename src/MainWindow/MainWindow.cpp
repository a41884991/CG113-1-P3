#include "MainWindow.h"
#include "ControlWindow/ControlWindow.h"
#include "MainView/MainView.h"
#include "Track/Track.h"

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

    this->BindCallBack();

    controlWindow = new ControlWindow(window);
}

void MainWindow::Show()
{
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        ProcessInput(window);
        HandleControlData(controlWindow->GetControlData());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render
        // ------
        controlWindow->setTrackLength(view->GetTrack()->getTrackLength());
        controlWindow->Render();

        view->Render(deltaTime);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

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
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MainWindow::BindCallBack()
{
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow *window, int w, int h)
        {
            glViewport(0, 0, w, h);
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

void MainWindow::HandleControlData(const ControlData &controlData)
{
    view->OnControlData(controlData);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void MainWindow::ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        view->OnKey(GLFW_KEY_W, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        view->OnKey(GLFW_KEY_S, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        view->OnKey(GLFW_KEY_A, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        view->OnKey(GLFW_KEY_D, deltaTime);
}