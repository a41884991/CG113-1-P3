#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera/Camera.h"

class Model;
class ShaderProgram;
class Train
{
public:
    Train(const char *modelPath);

    void Render(ShaderProgram *program, glm::mat4 modelMat);

    const glm::mat4 getCameraViewMat() { return m_camera->GetViewMatrix(); }
    void moveCamera(glm::vec3 position, glm::vec3 front)
    {
        m_camera->setPosition(position);
        m_camera->setFront(front);
    }
    void setCameraUp(const glm::vec3 &up) { m_camera->setUp(up); }

    void setTime(float time) { m_time = time; }
    const float &getTime() const { return m_time; }

private:
    Model *m_model;
    glm::mat4 m_modelMat;
    Camera *m_camera;

    float m_time = 0.0f;
};
