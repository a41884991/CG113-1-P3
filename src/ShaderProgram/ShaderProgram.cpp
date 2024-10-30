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
        std::cout << "vertex error\n";
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        throw(infoLog);
    }

    std::cout << "vertex complete\n";

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        throw(infoLog);
    }

    std::cout << "fragment complete\n";

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

    std::cout << "program complete\n";

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
