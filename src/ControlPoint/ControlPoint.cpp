/* --- ControlPoint.cpp --- */

/* ------------------------------------------
author: User
date: 11/11/2024
------------------------------------------ */

#include "ControlPoint.h"
#include "ShaderProgram/ShaderProgram.h"
#include <iostream>

int ControlPoint::selectedIndex = -1;
bool ControlPoint::isInitalized = false;
GLuint ControlPoint::VAO = 0;
GLuint ControlPoint::VBO = 0;

ControlPoint::ControlPoint()
{
    // Constructor
    if (!isInitalized)
        Initialize();
}

ControlPoint::ControlPoint(glm::vec3 position, int index)
{
    if (!isInitalized)
        Initialize();

    this->position = position;
    this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    this->index = index;
    this->orientation = glm::vec3(0.0f, 1.0f, 0.0f);
}

ControlPoint::~ControlPoint()
{
    // Destructor
}

void ControlPoint::Render(ShaderProgram *program)
{
    glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
    if (index == selectedIndex)
        color.g = 1.0f;

    program->SetVec3("ourColor", color);

    program->SetMat4("model", this->CreateModelMatrix());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 42);
    glBindVertexArray(0);
}

void ControlPoint::RenderID(ShaderProgram *program)
{
    program->SetMat4("model", this->CreateModelMatrix());
    program->SetInt("ID", index + 1);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 42);
    glBindVertexArray(0);
}

void ControlPoint::setIndex(const int &newIndex)
{
    index = newIndex;
}

const int &ControlPoint::getIndex() const
{
    return index;
}

void ControlPoint::setSelectedIndex(const int &newIndex)
{
    selectedIndex = newIndex;
}

void ControlPoint::setPosition(const glm::vec3 &newPosition)
{
    position = newPosition;
}

const glm::vec3 &ControlPoint::getPosition() const
{
    return position;
}

void ControlPoint::setRotation(const glm::vec3 &newRotation)
{
    rotation = newRotation;
    computeOrient();
}

const glm::vec3 &ControlPoint::getRotation() const
{
    return rotation;
}

void ControlPoint::Initialize()
{
    float vertices[] = {
        -0.05f, -0.05f, -0.05f, 0.0f, 0.0f, -1.0f,
        0.05f, -0.05f, -0.05f, 0.0f, 0.0f, -1.0f,
        0.05f, 0.05f, -0.05f, 0.0f, 0.0f, -1.0f,
        0.05f, 0.05f, -0.05f, 0.0f, 0.0f, -1.0f,
        -0.05f, 0.05f, -0.05f, 0.0f, 0.0f, -1.0f,
        -0.05f, -0.05f, -0.05f, 0.0f, 0.0f, -1.0f,

        -0.05f, -0.05f, 0.05f, 0.0f, 0.0f, 1.0f,
        0.05f, -0.05f, 0.05f, 0.0f, 0.0f, 1.0f,
        0.05f, 0.05f, 0.05f, 0.0f, 0.0f, 1.0f,
        0.05f, 0.05f, 0.05f, 0.0f, 0.0f, 1.0f,
        -0.05f, 0.05f, 0.05f, 0.0f, 0.0f, 1.0f,
        -0.05f, -0.05f, 0.05f, 0.0f, 0.0f, 1.0f,

        -0.05f, 0.05f, 0.05f, -1.0f, 0.0f, 0.0f,
        -0.05f, 0.05f, -0.05f, -1.0f, 0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f, -1.0f, 0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f, -1.0f, 0.0f, 0.0f,
        -0.05f, -0.05f, 0.05f, -1.0f, 0.0f, 0.0f,
        -0.05f, 0.05f, 0.05f, -1.0f, 0.0f, 0.0f,

        0.05f, 0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
        0.05f, 0.05f, -0.05f, 1.0f, 0.0f, 0.0f,
        0.05f, -0.05f, -0.05f, 1.0f, 0.0f, 0.0f,
        0.05f, -0.05f, -0.05f, 1.0f, 0.0f, 0.0f,
        0.05f, -0.05f, 0.05f, 1.0f, 0.0f, 0.0f,
        0.05f, 0.05f, 0.05f, 1.0f, 0.0f, 0.0f,

        -0.05f, -0.05f, -0.05f, 0.0f, -1.0f, 0.0f,
        0.05f, -0.05f, -0.05f, 0.0f, -1.0f, 0.0f,
        0.05f, -0.05f, 0.05f, 0.0f, -1.0f, 0.0f,
        0.05f, -0.05f, 0.05f, 0.0f, -1.0f, 0.0f,
        -0.05f, -0.05f, 0.05f, 0.0f, -1.0f, 0.0f,
        -0.05f, -0.05f, -0.05f, 0.0f, -1.0f, 0.0f,

        // roof
        -0.05f, 0.05f, -0.05f, 0.0f, 0.707f, -0.707f,
        0.0f, 0.1f, 0.0f, 0.0f, 0.707f, -0.707f,
        0.05f, 0.05f, -0.05f, 0.0f, 0.707f, -0.707f,

        0.05f, 0.05f, -0.05f, 0.707f, 0.707f, 0.0f,
        0.0f, 0.1f, 0.0f, 0.707f, 0.707f, 0.0f,
        0.05f, 0.05f, 0.05f, 0.707f, 0.707f, 0.0f,

        0.05f, 0.05f, 0.05f, 0.0f, 0.707f, 0.707f,
        0.0f, 0.1f, 0.0f, 0.0f, 0.707f, 0.707f,
        -0.05f, 0.05f, 0.05f, 0.0f, 0.707f, 0.707f,

        -0.05f, 0.05f, 0.05f, -0.707f, 0.707f, 0.0f,
        0.0f, 0.1f, 0.0f, -0.707f, 0.707f, 0.0f,
        -0.05f, 0.05f, -0.05f, -0.707f, 0.707f, 0.0f};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    isInitalized = true;
}

void ControlPoint::computeOrient()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

    auto result = model * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    orientation = glm::vec3(result);
}

void ControlPoint::addRoation(const glm::vec3 &addRotation)
{
    this->rotation += addRotation;
    computeOrient();
}

glm::mat4 ControlPoint::CreateModelMatrix()
{
    glm::mat4 model(1.0f);

    model = glm::translate(model, this->position);
    model = glm::rotate(model, this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

    return model;
}
