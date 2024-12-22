/* --- Camera.h --- */

/* ------------------------------------------
Author: User
Date: 11/6/2024
------------------------------------------ */

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DataStructure.h"

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 4.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = -30.0f);
    ~Camera();

    glm::mat4 GetViewMatrix();

    void ProcessMouseMovement(double xOffset, double yOffset);

    void ProcessKeyboard(CameraMovement direction, float deltaTime);

    void SetStatus(CameraStatus status) { this->status = status; }

    const glm::vec3 &GetPosition() const { return position; }

    void setPosition(glm::vec3 &position) { this->position = position; }
    void setFront(glm::vec3 &front) { this->front = front; }
    void setUp(const glm::vec3 &up) { this->up = up; }

private:
    void UpdateCameraVectors();

private:
    CameraStatus status;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
};

#endif // CAMERA_H
