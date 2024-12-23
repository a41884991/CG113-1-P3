#include "DirectionalLight.h"
#include <iostream>

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : BasicLight(ambient, diffuse, specular)
{
    this->direction = direction;
}

void DirectionalLight::setProgramValue(ShaderProgram *program, std::string name)
{
    program->SetVec3((name + ".direction").c_str(), direction);
    program->SetVec3((name + ".ambient").c_str(), ambient);
    program->SetVec3((name + ".diffuse").c_str(), diffuse);
    program->SetVec3((name + ".specular").c_str(), specular);
}
