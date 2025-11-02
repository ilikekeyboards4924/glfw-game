#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory> // std::unique_ptr
#include <cmath> // floor
#include <cstdlib> // rand()
#include <ctime> // time()
#include <chrono> // more time stuff
#include <random>
#include <vector>
#include "global.h"
#include "chunk.h"
#include "cube.h"

#include <iostream>




Chunk::Chunk() {}

Chunk::Chunk(glm::vec3 positionVector) {
	this->init(positionVector);
}


void Chunk::init(glm::vec3 positionVector) {
	modelMatrix = glm::mat4(1.0f);

	glGenVertexArrays(1, &(this->VAO));
	glGenBuffers(1, &(this->positionBuffer));
	glGenBuffers(1, &(this->colorBuffer));

	meshLength = 0;

	position = positionVector;

	// different seed for each time the constructor runs / Chunk is initialized
	//auto now = std::chrono::system_clock::now();
	//auto duration_since_epoch = now.time_since_epoch();
	//auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration_since_epoch);
	//long long currentMilliseconds = milliseconds.count();
	//srand(currentMilliseconds); // set random number generator seed to current time


	for (int y = 0; y < 10; y++) {
		for (int z = 0; z < 10; z++) {
			for (int x = 0; x < 10; x++) {
				auto tempCube = std::make_unique<Cube>();
				tempCube->modelMatrix = glm::translate(tempCube->modelMatrix, glm::vec3((float)x + position.x, (float)y + position.y, (float)z + position.z));

				//if (rand() % 100 < 25) { // x% chance of removing block
				//	tiles[y * 100 + z * 10 + x * 1] = nullptr;
				//}
				//else {
				//	tiles[y * 100 + z * 10 + x * 1] = std::move(tempCube);
				//}

				tiles[y * 100 + z * 10 + x * 1] = std::move(tempCube);
			}
		}
	}
}

Cube* Chunk::getTile(int x, int y, int z) {
	if (x < 0 || x >= 10) return nullptr;
	if (y < 0 || y >= 10) return nullptr;
	if (z < 0 || z >= 10) return nullptr;

	return this->tiles[y * 100 + z * 10 + x * 1].get();
}


void Chunk::buildMesh() {
	//std::vector<GLfloat> vertices = std::vector();
	//std::vector<GLfloat> colors;
	vertices.clear();
	colors.clear();

	for (int y = 0; y < 10; y++) {
		for (int z = 0; z < 10; z++) {
			for (int x = 0; x < 10; x++) {
				Cube* tile = this->getTile(x, y, z);
				if (tile == nullptr) continue;

				Cube* front = this->getTile(x, y, z + 1);
				Cube* back = this->getTile(x, y, z - 1);
				Cube* left = this->getTile(x - 1, y, z);
				Cube* right = this->getTile(x + 1, y, z);
				Cube* top = this->getTile(x, y + 1, z);
				Cube* bottom = this->getTile(x, y - 1, z);

				
				for (int vertexIndex = 0; vertexIndex < 108; vertexIndex += 3) { // increase by 3 to get to the next vertex
					glm::vec3 vertex = glm::vec3(tile->vertices[vertexIndex], tile->vertices[vertexIndex + 1], tile->vertices[vertexIndex + 2]); // current vertex

					double face = floor(vertexIndex / 18);

					if (
						(face == 0 && front == nullptr) ||
						(face == 1 && back == nullptr) ||
						(face == 2 && left == nullptr) ||
						(face == 3 && right == nullptr) ||
						(face == 4 && top == nullptr) ||
						(face == 5 && bottom == nullptr)
					) {
						glm::vec4 worldVertex = tile->modelMatrix * glm::vec4(vertex.x, vertex.y, vertex.z, 1.0f);

						vertices.push_back(worldVertex.x);
						vertices.push_back(worldVertex.y);
						vertices.push_back(worldVertex.z);
					}
				}

				for (int colorIndex = 0; colorIndex < 144; colorIndex += 4) { // increase by 3 to get to the next vertex
					double face = floor(colorIndex / 24);

					if (
						(face == 0 && front == nullptr) ||
						(face == 1 && back == nullptr) ||
						(face == 2 && left == nullptr) ||
						(face == 3 && right == nullptr) ||
						(face == 4 && top == nullptr) ||
						(face == 5 && bottom == nullptr)
					) {
						glm::vec4 color = glm::vec4(tile->colors[colorIndex], tile->colors[colorIndex + 1], tile->colors[colorIndex + 2], tile->colors[colorIndex + 3]);

						colors.push_back(color.r);
						colors.push_back(color.g);
						colors.push_back(color.b);
						colors.push_back(color.a);
					}
				}
			}
		}
	}

	//glGenVertexArrays(1, &(this->VAO)); // make sure that the constructor for Cube runs AFTER glfw and GLAD are initialized or you WILL get an access violation
	//glGenBuffers(1, &(this->positionBuffer));
	//glGenBuffers(1, &(this->colorBuffer));

	const int verticesLength = vertices.size();
	const int colorsLength = colors.size();

	GLfloat* verticesArray = new GLfloat[verticesLength];
	GLfloat* colorsArray = new GLfloat[colorsLength];

	std::copy(vertices.begin(), vertices.end(), verticesArray);
	std::copy(colors.begin(), colors.end(), colorsArray);

	glBindVertexArray(VAO); // make VAO the current Vertex Array Object by binding it (always bind the vao before anything else and unbind it after everything else (everything besides EBO, EBO always last))

	// position stuff
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer); // bind the VBO specifying that its a GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesLength, verticesArray, GL_STATIC_DRAW); // add the vertices to the VBO

	glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // tell opengl how to read the vertices from the buffer
	glEnableVertexAttribArray(positionAttributeLocation); // enable the attribute so that opengl knows to use it (0 for location = 0)

	// color stuff
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colorsLength, colorsArray, GL_STATIC_DRAW);

	glVertexAttribPointer(colorAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(colorAttributeLocation);

	// unbind everything
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	meshLength = floor(verticesLength / 3);
}


void Chunk::draw() {
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &this->modelMatrix[0][0]);

	glBindVertexArray(VAO); // bind the vao so that opengl knows to use it for drawing
	glDrawArrays(GL_TRIANGLES, 0, meshLength); // 108/3, 36 vertices
	glBindVertexArray(0); // unbind
	//for (int i = 0; i < 1000; i++) {
	//	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &tiles[i]->modelMatrix[0][0]);
	//	tiles[i]->draw();
	//}
}