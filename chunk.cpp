#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory> // std::unique_ptr
#include "global.h"
#include "chunk.h"
#include "cube.h"




Chunk::Chunk() {
	for (int y = 0; y < 10; y++) {
		for (int z = 0; z < 10; z++) {
			for (int x = 0; x < 10; x++) {
				auto tempCube = std::make_unique<Cube>();
				tempCube->modelMatrix = glm::translate(tempCube->modelMatrix, glm::vec3((float)x, (float)y, (float)z));
				tiles[y * 100 + z * 10 + x * 1] = std::move(tempCube);
			}
		}
	}
}


void Chunk::draw() {
	for (int i = 0; i < 1000; i++) {
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &tiles[i]->modelMatrix[0][0]);
		tiles[i]->draw();
	}
}