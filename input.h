#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

static double oldMousePosX = 0;
static double oldMousePosY = 0;
static double mousePosX = 0;
static double mousePosY = 0;

extern double movementX;
extern double movementY;

void keyHandler(GLFWwindow* window);

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

#endif