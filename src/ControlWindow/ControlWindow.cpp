#include "ControlWindow.h"

ControlWindow::ControlWindow(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    m_controlData.trainStatus = TrainStatus::STOP;
    m_controlData.cameraStatus = CameraStatus::WORLD;
    m_controlData.trackMode = TrackMode::LINEAR;
    m_controlData.cardinalTension = 0.5f;
    m_controlData.trainTime = 0.0f;
    m_controlData.isParameterization = false;
    m_controlData.currentLength = 0.0f;

    // showDemoWindow = true;
    trainSpeed = 0.005f;
    trainSpeedParam = 0.5f;
    isTrainTimeDisabled = false;

    trackLength = 11.20f;
}

ControlWindow::~ControlWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ControlWindow::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // if (this->showDemoWindow)
    //     ImGui::ShowDemoWindow(&this->showDemoWindow);

    ImGui::Begin("Control Window");
    {
        ImGui::Text("Train Status");
        ImGui::Separator();
        float buttonWidth = (ImGui::GetContentRegionAvail().x - 20) / 2;
        if (ImGui::Button(("Run"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.trainStatus = TrainStatus::RUN;
            isTrainTimeDisabled = true;
        }
        ImGui::SameLine();
        if (ImGui::Button(("Stop"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.trainStatus = TrainStatus::STOP;
            isTrainTimeDisabled = false;
        }

        if (m_controlData.isParameterization)
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 1.0f, 1.0f));
        if (ImGui::Button(("Parameterization"), ImVec2(2 * buttonWidth, 0)))
        {
            m_controlData.isParameterization = !m_controlData.isParameterization;
            switchLengthTime();
        }
        if (m_controlData.isParameterization)
            ImGui::PopStyleColor();

        if (isTrainTimeDisabled)
            ImGui::BeginDisabled();
        if (!m_controlData.isParameterization)
            ImGui::SliderFloat("Train Time", &m_controlData.trainTime, 0.0f, 1.0f);
        else
            ImGui::SliderFloat("Train Time", &m_controlData.currentLength, 0.0f, trackLength);
        if (isTrainTimeDisabled)
            ImGui::EndDisabled();

        if (!m_controlData.isParameterization)
            ImGui::SliderFloat("Train Speed", &trainSpeed, 0.001f, 0.01f);
        else
            ImGui::SliderFloat("Train Speed", &trainSpeedParam, 0.05f, 1.0f);
    }
    ImGui::Text("    ");
    {
        ImGui::Text("Camera Location");
        ImGui::Separator();
        float buttonWidth = (ImGui::GetContentRegionAvail().x - 20) / 3;
        if (ImGui::Button(("World"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.cameraStatus = CameraStatus::WORLD;
        }
        ImGui::SameLine();
        if (ImGui::Button(("Train"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.cameraStatus = CameraStatus::TRAIN;
        }
        ImGui::SameLine();
        if (ImGui::Button(("Top"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.cameraStatus = CameraStatus::TOP;
        }
    }
    ImGui::Text("    ");
    {
        ImGui::Text("Track Option");
        ImGui::Separator();

        const char *modes[] = {"Linear", "Cubic B-Spline", "Cardinal Cubic"};
        static int currentMode = 0;
        ImGui::Combo("Track Mode", &currentMode, modes, IM_ARRAYSIZE(modes));
        switch (currentMode)
        {
        case 0:
            m_controlData.trackMode = TrackMode::LINEAR;
            break;
        case 1:
            m_controlData.trackMode = TrackMode::CUBIC_B_SPLINE;
            break;
        case 2:
            m_controlData.trackMode = TrackMode::CARDINAL_CUBIC;
            break;
        default:
            m_controlData.trackMode = TrackMode::LINEAR;
            break;
        }

        ImGui::SliderFloat("Cardinal Tension", &m_controlData.cardinalTension, 0.0f, 1.0f);

        m_controlData.pointRoation = ControlPointRotation::NONE;
        float buttonWidth = (ImGui::GetContentRegionAvail().x - 20) / 2;
        if (ImGui::Button(("X+"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.pointRoation = ControlPointRotation::X_PLUS;
        }
        ImGui::SameLine();
        if (ImGui::Button(("X-"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.pointRoation = ControlPointRotation::X_MINUS;
        }

        if (ImGui::Button(("Z+"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.pointRoation = ControlPointRotation::Z_PLUS;
        }
        ImGui::SameLine();
        if (ImGui::Button(("Z-"), ImVec2(buttonWidth, 0)))
        {
            m_controlData.pointRoation = ControlPointRotation::X_MINUS;
        }
    }
    ImGui::End();

    ImGui::Render();

    if (m_controlData.trainStatus == TrainStatus::RUN)
    {
        m_controlData.trainTime += trainSpeed;
        m_controlData.currentLength += trainSpeedParam;
    }

    if (m_controlData.trainTime > 1.0f)
        m_controlData.trainTime -= 1.0f;

    if (m_controlData.currentLength > trackLength)
        m_controlData.currentLength -= trackLength;
}

void ControlWindow::switchLengthTime()
{
    if (m_controlData.isParameterization)
        m_controlData.currentLength = m_controlData.trainTime * trackLength;
    else
        m_controlData.trainTime = m_controlData.currentLength / trackLength;
}
