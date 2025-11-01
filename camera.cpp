#include <glm/glm.hpp>
#include <algorithm> // for std::min and std::max
#include <iostream>
#include <cmath>
#include "camera.h"



Camera::Camera() {
	position = glm::vec3(0, 0, 3);
	pitch = 0;
	yaw = 0;

	front = glm::vec3(0, 0, 0);
	frontXZ = glm::vec3(0, 0, 0);
	right = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);

	movementSpeed = 0.1;
}

void Camera::normalizeCameraVectors() {
	front = glm::normalize(front);
	frontXZ = glm::normalize(frontXZ);
	right = glm::normalize(right);
	up = glm::normalize(up);
}

void Camera::calculateCameraVectors() {
	double yawRadians = glm::radians(yaw);
	double pitchRadians = glm::radians(pitch);

	front = glm::vec3(cos(yawRadians) * cos(pitchRadians), sin(pitchRadians), sin(yawRadians) * cos(pitchRadians));
	frontXZ = glm::vec3(cos(yawRadians) * cos(pitchRadians), 0, sin(yawRadians) * cos(pitchRadians));
	right = glm::cross(front, up);

	normalizeCameraVectors();
}

void Camera::updateCamera() {
	//pitch = (int)std::floor(-mousePosY) % 360;
	//yaw = (int)std::floor(mousePosX) % 360;

	pitch = std::max(-90 + 0.001, std::min(pitch, 90 - 0.001));
	calculateCameraVectors();

	//std::cout << front[0] << "   " << front[2] << std::endl;
	//std::cout << pitch << "   " << -mousePosY << std::endl;
}