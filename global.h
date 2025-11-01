#ifndef GLOBAL_H
#define GLOBAL_H

#include "camera.h"
#include "cube.h"

extern double mousePosX, mousePosY;
extern Camera camera;
extern Cube* cube;

extern float deltaTime; // specify float because glm is strange about it being a double

#endif