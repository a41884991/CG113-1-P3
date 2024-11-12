/* --- ShaderProgram.cpp --- */

/* ------------------------------------------
author: User
date: 10/30/2024
------------------------------------------ */

#include "ShaderProgram.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram(const char *vertexShaderFile, const char *fragmentShaderFile)
{
    std::ifstream vertexInput;
    std::ifstream fragmentInput;

    vertexInput.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentInput.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    vertexInput.open(vertexShaderFile);
    fragmentInput.open(fragmentShaderFile);

    std::stringstream vertexStream, fragmentStream;

    vertexStream << vertexInput.rdbuf();
    fragmentStream << fragmentInput.rdbuf();

    vertexInput.close();
    fragmentInput.close();

    std::string vertexString, fragmentString;
    vertexString = vertexStream.str();
    fragmentString = fragmentStream.str();

    const char *vertexCode = vertexString.c_str();
    const char *fragmentCode = fragmentString.c_str();

    GLuint vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        throw(infoLog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        throw(infoLog);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        throw(infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

ShaderProgram::~ShaderProgram()
{
    // Destructor
}

void ShaderProgram::Use()
{
    glUseProgram(ID);
}

void ShaderProgram::SetMat4(const char *name, glm::mat4 &matrix) const
{
    GLuint uniformLocation = glGetUniformLocation(this->ID, name);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetInt(const char *name, int value) const
{
    GLuint uniformLocation = glGetUniformLocation(this->ID, name);
    glUniform1i(uniformLocation, value);
}

void ShaderProgram::SetFloat(const char *name, float value) const
{
    GLuint uniformLocation = glGetUniformLocation(this->ID, name);
    glUniform1f(uniformLocation, value);
}

void ShaderProgram::SetVec3(const char *name, glm::vec3 vec) const
{
    GLuint uniformLocation = glGetUniformLocation(this->ID, name);
    glUniform3fv(uniformLocation, 1, glm::value_ptr(vec));
}
