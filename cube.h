#ifndef CUBE_H
#define CUBE_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Cube {
public:
    glm::mat4 modelMatrix;

    GLuint VAO, positionBuffer, colorBuffer; // vertex array object, vertex buffer object

    GLfloat vertices[108];
    GLfloat colors[144];

    Cube();

    void draw();
};

#endif