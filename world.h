#ifndef WORLD_H
#define WORLD_H


#include <vector>
#include "chunk.h"

class World {
public:
	//Chunk* loadedChunks = new Chunk[100]; // is loadedChunks an incorrect name?
	std::vector<Chunk> loadedChunks;

	GLuint VAO, positionBuffer, colorBuffer;
	int meshLength;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;

	World();

	void init();

	void buildWorldMesh();

	void draw();
};

#endif