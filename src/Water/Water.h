#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "DataStructure.h"
class ShaderProgram;
class Water
{
public:
    Water(unsigned int width = 10, unsigned int height = 10);
    void update(float dt);
    void render(ShaderProgram *program);

private:
    void initBuffers();

private:
    GLuint VAO, VBO, EBO;
    unsigned int width, height;
    float time;
    glm::mat4 modelMat;
    std::vector<glm::vec3> positions;
    std::vector<unsigned int> indices;
    Wave wave;
};
