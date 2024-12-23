#pragma once

#include "BasicLight.h"

class PointLight : private BasicLight
{
public:
    PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void setProgramValue(ShaderProgram *program, std::string name) override;
    void setPosition(const glm::vec3 &position) { this->position = position; }

private:
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;
};
