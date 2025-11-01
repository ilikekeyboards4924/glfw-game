#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "global.h"
#include "cube.h"

Cube::Cube() {
    modelMatrix = glm::mat4(1.0f);

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

    GLfloat tempColors[144] = {
        0.1, 0.5, 0.5, 1.0,
        0.2, 0.5, 0.5, 1.0,
        0.3, 0.5, 0.5, 1.0,
        0.4, 0.5, 0.5, 1.0,
        0.5, 0.5, 0.5, 1.0,
        0.6, 0.5, 0.5, 1.0,

        0.7, 0.3, 0.7, 1.0,
        0.6, 0.3, 0.3, 1.0,
        0.5, 0.3, 0.2, 1.0,
        0.4, 0.3, 0.3, 1.0,
        0.3, 0.3, 0.5, 1.0,
        0.2, 0.3, 0.3, 1.0,

        0.1, 0.1, 0.1, 1.0,
        0.1, 0.1, 0.1, 1.0,
        0.1, 0.5, 0.1, 1.0,
        0.1, 0.1, 0.1, 1.0,
        0.2, 0.1, 0.1, 1.0,
        0.1, 0.1, 0.1, 1.0,

        0.7, 0.7, 0.7, 1.0,
        0.7, 0.7, 0.7, 1.0,
        0.7, 0.7, 0.7, 1.0,
        0.7, 0.7, 0.7, 1.0,
        0.7, 0.7, 0.7, 1.0,
        0.7, 0.7, 0.7, 1.0,

        0.2, 0.2, 0.8, 1.0,
        0.2, 0.2, 0.8, 1.0,
        0.2, 0.2, 0.8, 1.0,
        0.2, 0.2, 0.8, 1.0,
        0.2, 0.2, 0.8, 1.0,
        0.2, 0.2, 0.8, 1.0,

        0.2, 0.8, 0.2, 1.0,
        0.2, 0.8, 0.2, 1.0,
        0.2, 0.8, 0.2, 1.0,
        0.2, 0.8, 0.2, 1.0,
        0.2, 0.8, 0.2, 1.0,
        0.2, 0.8, 0.2, 1.0,
    };

    for (int i = 0; i < 108; i++) {
        vertices[i] = tempVertices[i];
    }

    for (int i = 0; i < 144; i++) {
        colors[i] = tempColors[i];
    }

    glGenVertexArrays(1, &(this->VAO)); // make sure that the constructor for Cube runs AFTER glfw and GLAD are initialized or you WILL get an access violation
    glGenBuffers(1, &(this->positionBuffer));
    glGenBuffers(1, &(this->colorBuffer));

    glBindVertexArray(VAO); // make VAO the current Vertex Array Object by binding it (always bind the vao before anything else and unbind it after everything else (everything besides EBO, EBO always last))

    // position stuff
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer); // bind the VBO specifying that its a GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 108, vertices, GL_STATIC_DRAW); // add the vertices to the VBO

    glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // tell opengl how to read the vertices from the buffer
    glEnableVertexAttribArray(positionAttributeLocation); // enable the attribute so that opengl knows to use it (0 for location = 0)

    // color stuff
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 144, colors, GL_STATIC_DRAW);

    glVertexAttribPointer(colorAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(colorAttributeLocation);

    // unbind everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Cube::draw() {
    glBindVertexArray(VAO); // bind the vao so that opengl knows to use it for drawing
    glDrawArrays(GL_TRIANGLES, 0, 36); // 108/3
    glBindVertexArray(0); // unbind
}