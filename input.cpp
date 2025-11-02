#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "input.h"
#include "camera.h"
#include "global.h"

double movementX = 0;
double movementY = 0;

void keyHandler(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.position = camera.position + camera.up * camera.movementSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.position = camera.position + -camera.up * camera.movementSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.position = camera.position + camera.up * camera.movementSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera.position = camera.position + -camera.up * camera.movementSpeed * deltaTime;
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.position = camera.position + camera.frontXZ * camera.movementSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.position = camera.position + -camera.frontXZ * camera.movementSpeed * deltaTime;
    }


    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.position = camera.position + camera.right * camera.movementSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.position = camera.position + -camera.right * camera.movementSpeed * deltaTime;
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

    //std::cout << movementX << "   " << movementY << "   " << camera.yaw << "   " << camera.pitch << std::endl;
}