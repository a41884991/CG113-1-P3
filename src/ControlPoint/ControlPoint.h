/* --- ControlPoint.h --- */

/* ------------------------------------------
Author: User
Date: 11/11/2024
------------------------------------------ */

#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram;

class ControlPoint
{
public:
    ControlPoint();

    ControlPoint(glm::vec3 position, int index);
    ~ControlPoint();

    void Render(ShaderProgram *program);
    void RenderID(ShaderProgram *program);

    void setIndex(const int &newIndex);
    const int &getIndex() const;

    void setSelectedIndex(const int &newIndex);

    void setPosition(const glm::vec3 &newPosition);
    const glm::vec3 &getPosition() const;

    void setRotation(const glm::vec3 &newRotation);
    const glm::vec3 &getRotation() const;

    const glm::vec3 &getOrientation() const { return orientation; }

private:
    glm::mat4 CreateModelMatrix();

    void Initialize();
    void computeOrient();

private:
    int index;
    static int selectedIndex;
    static bool isInitalized;
    static GLuint VAO;
    static GLuint VBO;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 orientation;
};

#endif // CONTROLPOINT_H
