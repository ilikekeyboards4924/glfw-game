#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "cube.h"

Cube::Cube() {
    GLfloat tempVertices[108] = { // use this to define vertices
        // Front face (z = 0.5)
        -0.5, -0.5, 0.5,  // bottom-left
        0.5, -0.5, 0.5,  // bottom-right
        0.5, 0.5, 0.5,  // top-right
        0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        -0.5, -0.5, 0.5,

        // Back face (z = -0.5)
        -0.5, -0.5, -0.5,
        -0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, -0.5, -0.5,
        -0.5, -0.5, -0.5,

        // Left face (x = -0.5)
        -0.5, -0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5, -0.5,
        -0.5, -0.5, -0.5,

        // Right face (x = 0.5)
        0.5, -0.5, -0.5,
        0.5, 0.5, -0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, -0.5, 0.5,
        0.5, -0.5, -0.5,

        // Top face (y = 0.5)
        -0.5, 0.5, -0.5,
        -0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5,
        -0.5, 0.5, -0.5,

        // Bottom face (y = -0.5)
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5, 0.5,
        0.5, -0.5, 0.5,
        -0.5, -0.5, 0.5,
        -0.5, -0.5, -0.5,
    };

    for (int i = 0; i < 108; i++) {
        vertices[i] = tempVertices[i];
    }

    glGenVertexArrays(1, &(this->VAO)); // make sure that the constructor for Cube runs AFTER glfw and GLAD are initialized or you WILL get an access violation
    glGenBuffers(1, &(this->VBO));


    glBindVertexArray(VAO); // make VAO the current Vertex Array Object by binding it (always bind the vao before anything else and unbind it after everything else (everything besides EBO, EBO always last))

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind the VBO specifying that its a GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // add the vertices to the VBO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // tell opengl how to read the vertices from the buffer
    glEnableVertexAttribArray(0); // enable the attribute so that opengl knows to use it (0 for location = 0)

    // unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Cube::draw() {
    glBindVertexArray(VAO); // bind the vao so that opengl knows to use it for drawing
    glDrawArrays(GL_TRIANGLES, 0, 108);
    glBindVertexArray(0); // unbind
}