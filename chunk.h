#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <memory>
#include <vector>
#include "cube.h"

class Chunk {
public:
	glm::mat4 modelMatrix;

	GLuint VAO, positionBuffer, colorBuffer;
	int meshLength; // theres probably a better way than this
	
	glm::vec3 position;
	
	std::array<std::unique_ptr<Cube>, 1000> tiles;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;

	Chunk();

	Chunk(glm::vec3 positionVector);

	void init(glm::vec3 positionVector);

	Cube* getTile(int x, int y, int z);

	void buildMesh();

	void draw();
};

#endif