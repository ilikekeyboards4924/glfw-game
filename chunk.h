#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <memory>
#include "cube.h"

class Chunk {
public:
	//Cube* tiles[100];
	std::array<std::unique_ptr<Cube>, 1000> tiles;

	Chunk();

	void draw();
};

#endif