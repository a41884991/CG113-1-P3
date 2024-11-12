/* --- Camera.cpp --- */

/* ------------------------------------------
author: User
date: 11/6/2024
------------------------------------------ */

#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;

    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->movementSpeed = 2.5f;
    this->mouseSensitivity = 0.1f;

    this->status = CameraStatus::WORLD;

    UpdateCameraVectors();
}

Camera::~Camera()
{
    // Destructor
}

glm::mat4 Camera::GetViewMatrix()
{
    if (status == CameraStatus::TOP)
        return glm::lookAt(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    return glm::lookAt(position, position + front, up);
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(newFront);
    // also re-calculate the Right and Up vector
    this->right = glm::normalize(glm::cross(this->front, this->worldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->up = glm::normalize(glm::cross(this->right, this->front));
}