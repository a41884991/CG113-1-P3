#include "Train.h"
#include "Model/Model.h"
#include "ShaderProgram/ShaderProgram.h"
#include "DataStructure.h"

Train::Train(const char *modelPath)
{
    m_model = new Model(modelPath);

    m_modelMat = glm::mat4(1.0f);
    m_modelMat = glm::rotate(m_modelMat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    m_modelMat = glm::scale(m_modelMat, glm::vec3(0.05f, 0.05f, 0.05f));

    m_camera = new Camera(glm::vec3(0.0f, 4.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -30.0f);
    m_camera->SetStatus(CameraStatus::TRAIN);
}

void Train::Render(ShaderProgram *program, glm::mat4 modelMat)
{
    program->SetMat4("model", modelMat * m_modelMat);
    m_model->Render(program);
}
