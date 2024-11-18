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

    void setIndex(const int &newIndex);
    const int &getIndex() const;

    void setSelectedIndex(const int &newIndex);

private:
    glm::mat4 CreateModelMatrix();

    void Initialize();

private:
    int index;
    static int selectedIndex;
    static bool isInitalized;
    static GLuint VAO;
    static GLuint VBO;

    glm::vec3 position;
    glm::vec3 rotation;
};

#endif // CONTROLPOINT_H
