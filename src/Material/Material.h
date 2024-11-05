/* --- Material.h --- */

/* ------------------------------------------
Author: User
Date: 11/5/2024
------------------------------------------ */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Material {
public:
    Material(const char* path);
    ~Material();

    void Use();

private:
    GLuint texture;
};

#endif // MATERIAL_H
