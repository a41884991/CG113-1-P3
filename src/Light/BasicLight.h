#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "string"
#include "ShaderProgram/ShaderProgram.h"
class BasicLight
{
public:
    BasicLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    virtual void setProgramValue(ShaderProgram *program, std::string name) {};

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};
