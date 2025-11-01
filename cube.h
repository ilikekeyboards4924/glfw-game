#ifndef CUBE_H
#define CUBE_H

#include <GLFW/glfw3.h>

class Cube {
public:
    GLuint VAO, VBO;

    GLfloat vertices[108];

    Cube();

    void draw();
};

#endif