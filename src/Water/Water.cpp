#include "Water.h"
#include "ShaderProgram/ShaderProgram.h"

#include <iostream>

Water::Water(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    time = 0;
    modelMat = glm::mat4(1.0f);
    int widthMove = static_cast<int>(width / 2);
    int heightMove = static_cast<int>(height / 2);
    modelMat = glm::translate(modelMat, glm::vec3(-widthMove, 1.0f, -heightMove));

    wave = {glm::vec2(1.0f, 0.0f), 0.1, 2.0, glm::vec4(0.0f, 1.0f, 1.0f, 0.5f)};

    initBuffers();
}

void Water::update(float dt)
{
    float speed = 1.0f;
    time += dt * speed;
}

void Water::render(ShaderProgram *program)
{
    program->SetMat4("model", modelMat);
    program->SetVec2("wave.direction", wave.direction);
    program->SetFloat("wave.amplitude", wave.amplitude);
    program->SetFloat("wave.waveLength", wave.waveLength);
    program->SetVec4("color", wave.color);
    program->SetFloat("time", time);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Water::initBuffers()
{
    positions.clear();
    positions.reserve(width * 1 + height * 1);
    indices.clear();

    for (int y = 0; y <= height; ++y)
    {
        for (int x = 0; x <= width; ++x)
        {
            positions.push_back(glm::vec3((float)x, 0.0f, (float)y));
        }
    }

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            indices.push_back(y * (width + 1) + x);
            indices.push_back((y + 1) * (width + 1) + x);
            indices.push_back(y * (width + 1) + x + 1);

            indices.push_back(y * (width + 1) + x + 1);
            indices.push_back((y + 1) * (width + 1) + x);
            indices.push_back((y + 1) * (width + 1) + x + 1);
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
