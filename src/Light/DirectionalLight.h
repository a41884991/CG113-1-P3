#pragma once

#include "BasicLight.h"

class DirectionalLight : private BasicLight
{
public:
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void setProgramValue(ShaderProgram *program, std::string name) override;

private:
    glm::vec3 direction;
};
