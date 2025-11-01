#include <GLFW/glfw3.h>
#include <iostream>
#include "input.h"
#include "camera.h"
#include "global.h"

double movementX = 0;
double movementY = 0;

void keyHandler(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        std::cout << "E pressed" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "W pressed" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        std::cout << "S pressed" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        std::cout << "A pressed" << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        std::cout << "D pressed" << std::endl;
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    mousePosX = xpos;
    mousePosY = ypos;
    
    movementX = mousePosX - oldMousePosX;
    movementY = mousePosY - oldMousePosY;

    oldMousePosX = mousePosX;
    oldMousePosY = mousePosY;

    double sensitivityX = 0.3;
    double sensitivityY = 0.3;
    camera.yaw += movementX * sensitivityX;
    camera.pitch -= movementY * sensitivityY; // gotta do subtraction instead of addition because an increase in Y in screen space goes in the opposite direction of an increase in Y in clip space

    std::cout << movementX << "   " << movementY << "   " << camera.yaw << "   " << camera.pitch << std::endl;
}