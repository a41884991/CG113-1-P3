#include "PointLight.h"
#include <iostream>

PointLight::PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : BasicLight(ambient, diffuse, specular)
{
    this->position = position;

    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;
}

void PointLight::setProgramValue(ShaderProgram *program, std::string name)
{
    program->SetVec3((name + ".position").c_str(), position);
    program->SetVec3((name + ".ambient").c_str(), ambient);
    program->SetVec3((name + ".diffuse").c_str(), diffuse);
    program->SetVec3((name + ".specular").c_str(), specular);
    program->SetFloat((name + ".constant").c_str(), constant);
    program->SetFloat((name + ".linear").c_str(), linear);
    program->SetFloat((name + ".quadratic").c_str(), quadratic);
}
