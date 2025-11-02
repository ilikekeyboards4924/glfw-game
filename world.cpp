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
	loadedChunks.resize(100);
	//Chunk* loadedChunks = new Chunk[100]; // for some reason this works now that its in the constructor?????

}

void World::init() {
	//Chunk* loadedChunks = new Chunk[100]; // is loadedChunks an incorrect name?

	GLuint VAO, positionBuffer, colorBuffer;
	int meshLength = 0;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;

	glGenVertexArrays(1, &(this->VAO)); // make sure that the constructor for Cube runs AFTER glfw and GLAD are initialized or you WILL get an access violation
	glGenBuffers(1, &(this->positionBuffer));
	glGenBuffers(1, &(this->colorBuffer));

	for (int z = 0; z < 10; z++) {
		for (int x = 0; x < 10; x++) {
			loadedChunks[z * 10 + x * 1].init(glm::vec3((float)x * 10.0f, (float)x * (float)z * 0.0f, (float)z * 10.0f));
			loadedChunks[z * 10 + x * 1].buildMesh();
		}
	}

	//for (int z = 0; z < 10; z++) {
	//	for (int x = 0; x < 10; x++) {
	//		loadedChunks[z * 10 + x * 1].init(glm::vec3((float)x * 10.0f, 0.0f, (float)z * 10.0f));
	//		loadedChunks[z * 10 + x * 1].buildMesh();
	//	}
	//}
	buildWorldMesh();
}

void World::buildWorldMesh() {
	//std::vector<GLfloat> vertices;
	//std::vector<GLfloat> colors;
	vertices.clear();
	colors.clear();
	
	for (int i = 0; i < 100; i++) {
		loadedChunks[i].buildMesh();



		vertices.insert(vertices.end(), loadedChunks[i].vertices.begin(), loadedChunks[i].vertices.end());
		colors.insert(colors.end(), loadedChunks[i].colors.begin(), loadedChunks[i].colors.end());
	}
	
	const int verticesLength = vertices.size();
	const int colorsLength = colors.size();
	
	//GLfloat* verticesArray = new GLfloat[verticesLength];
	//GLfloat* colorsArray = new GLfloat[colorsLength];

	//if (verticesArray == nullptr) {
	//	std::cout << "verticesArray not working" << std::endl;
	//}
	//if (colorsArray == nullptr) {
	//	std::cout << "colorsArray not working" << std::endl;
	//}

	//std::copy(vertices.begin(), vertices.end(), verticesArray);
	//std::copy(colors.begin(), colors.end(), colorsArray);
	
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
	glDrawArrays(GL_TRIANGLES, 0, meshLength); // 108/3, 36 vertices
	glBindVertexArray(0); // unbind

	//std::cout << meshLength << std::endl;
	std::cout << "World: vertices = " << vertices.size()
		<< " colors = " << colors.size()
		<< " meshLength = " << meshLength << std::endl;

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "GL ERROR after buildWorldMesh: 0x" << std::hex << err << std::dec << std::endl;
	}
	//for (int z = 0; z < 10; z++) {
	//	for (int x = 0; x < 10; x++) {
	//		loadedChunks[z * 10 + x * 1].draw();
	//	}
	//}


	//for (int z = 0; z < 10; z++) {
	//	for (int x = 0; x < 10; x++) {
	//		loadedChunks[z * 10 + x * 1].draw();
	//	}
	//}

	//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &this->modelMatrix[0][0]); // do i need this for world.cpp?

	//glBindVertexArray(VAO); // bind the vao so that opengl knows to use it for drawing
	//glDrawArrays(GL_TRIANGLES, 0, meshLength); // 108/3, 36 vertices
	//glBindVertexArray(0); // unbind
}

//class World {
//public:
//	Chunk* loadedChunks = new Chunk[100]; // is loadedChunks an incorrect name?
//
//	GLuint VAO, positionBuffer, colorBuffer;
//	int meshLength = 0;
//
//	std::vector<GLfloat> vertices;
//	std::vector<GLfloat> colors;
//
//	World() {
//		// initialize all the chunks
//		for (int z = 0; z < 10; z++) {
//			for (int x = 0; x < 10; x++) {
//				loadedChunks[z * 10 + x * 1].init(glm::vec3((float)x * 10.0f, 0.0f, (float)z * 10.0f));
//			}
//		}
//	}
//
//	void init() {
//		glGenVertexArrays(1, &(this->VAO)); // make sure that the constructor for Cube runs AFTER glfw and GLAD are initialized or you WILL get an access violation
//		glGenBuffers(1, &(this->positionBuffer));
//		glGenBuffers(1, &(this->colorBuffer));
//	}
//
//	void buildWorldMesh() {
//		//std::vector<GLfloat> vertices;
//		//std::vector<GLfloat> colors;
//		vertices.clear();
//		colors.clear();
//
//		for (int i = 0; i < 100; i++) {
//			loadedChunks[i].buildMesh();
//
//
//
//			vertices.insert(vertices.begin(), vertices.end(), loadedChunks[i].vertices.end());
//			colors.insert(colors.begin(), colors.end(), loadedChunks[i].colors.end());
//		}
//
//		const int verticesLength = vertices.size();
//		const int colorsLength = colors.size();
//
//		GLfloat* verticesArray = new GLfloat[verticesLength];
//		GLfloat* colorsArray = new GLfloat[colorsLength];
//
//		std::copy(vertices.begin(), vertices.end(), verticesArray);
//		std::copy(colors.begin(), colors.end(), colorsArray);
//
//		glBindVertexArray(VAO); // make VAO the current Vertex Array Object by binding it (always bind the vao before anything else and unbind it after everything else (everything besides EBO, EBO always last))
//
//		// position stuff
//		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer); // bind the VBO specifying that its a GL_ARRAY_BUFFER
//		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticesLength, verticesArray, GL_STATIC_DRAW); // add the vertices to the VBO
//
//		glVertexAttribPointer(positionAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // tell opengl how to read the vertices from the buffer
//		glEnableVertexAttribArray(positionAttributeLocation); // enable the attribute so that opengl knows to use it (0 for location = 0)
//
//		// color stuff
//		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * colorsLength, colorsArray, GL_STATIC_DRAW);
//
//		glVertexAttribPointer(colorAttributeLocation, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
//		glEnableVertexAttribArray(colorAttributeLocation);
//
//		// unbind everything
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//
//		meshLength = floor(verticesLength / 3);
//	}
//
//	void draw() {
//		for (int z = 0; z < 10; z++) {
//			for (int x = 0; x < 10; x++) {
//				loadedChunks[z * 10 + x * 1].draw();
//			}
//		}
//
//		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &this->modelMatrix[0][0]); // do i need this for world.cpp?
//
//		//glBindVertexArray(VAO); // bind the vao so that opengl knows to use it for drawing
//		//glDrawArrays(GL_TRIANGLES, 0, meshLength); // 108/3, 36 vertices
//		//glBindVertexArray(0); // unbind
//	}
//};