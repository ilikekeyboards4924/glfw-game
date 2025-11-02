#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "world.h"
#include "chunk.h"
#include "global.h"

#include <iostream>

// will contain loaded chunks, (time of day?), the draw call for all vertices in the world (its faster if you draw every single thing in one draw call)



World::World() {
	loadedChunks.resize(100); // allocate memory for (x number) of chunks
}

void World::init() {
	GLuint VAO, positionBuffer, colorBuffer;
	int meshLength = 0;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;

	glGenVertexArrays(1, &(this->VAO)); // make sure that the constructor for Cube runs AFTER glfw and GLAD are initialized or you WILL get an access violation
	glGenBuffers(1, &(this->positionBuffer));
	glGenBuffers(1, &(this->colorBuffer));

	for (int y = 0; y < 1; y++) {
		for (int z = 0; z < 10; z++) {
			for (int x = 0; x < 10; x++) {
				// i NEED to fix these indices, this is disgusting
				loadedChunks[y * (10 * 10) + z * (10) + x * 1].init(glm::vec3((float)x * 10.0f, (float)y * 10.0f, (float)z * 10.0f));
				loadedChunks[y * (10 * 10) + z * (10) + x * 1].buildMesh();
			}
		}
	}

	buildWorldMesh();
}

void World::buildWorldMesh() {
	vertices.clear();
	colors.clear();
	
	for (int i = 0; i < 100; i++) {
		loadedChunks[i].buildMesh();

		vertices.insert(vertices.end(), loadedChunks[i].vertices.begin(), loadedChunks[i].vertices.end());
		colors.insert(colors.end(), loadedChunks[i].colors.begin(), loadedChunks[i].colors.end());
	}
	
	const int verticesLength = vertices.size();
	const int colorsLength = colors.size();

	glBindVertexArray(VAO); // make VAO the current Vertex Array Object by binding it (always bind the vao before anything else and unbind it after everything else (everything besides EBO, EBO always last))
	
	// position stuff
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer); // bind the VBO specifying that its a GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesLength, vertices.data(), GL_STATIC_DRAW); // add the vertices to the VBO
	
	glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // tell opengl how to read the vertices from the buffer
	glEnableVertexAttribArray(positionAttributeLocation); // enable the attribute so that opengl knows to use it (0 for location = 0)
	
	// color stuff
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colorsLength, colors.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(colorAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(colorAttributeLocation);
	
	// unbind everything
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	meshLength = floor(verticesLength / 3);
}

void World::draw() {
	glBindVertexArray(VAO); // bind the vao so that opengl knows to use it for drawing
	glDrawArrays(GL_TRIANGLES, 0, meshLength); // meshLength is the number of points to draw / iterate through
	glBindVertexArray(0); // unbind

	//std::cout << meshLength << std::endl;
}
