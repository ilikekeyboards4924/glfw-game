#include <glm/glm.hpp>
#include <algorithm> // for std::min and std::max
#include <iostream>
#include <cmath>
#include "camera.h"



Camera::Camera() {
	position = glm::vec3(0, 0, 3);
	pitch = 0;
	yaw = 270;

	front = glm::vec3(0, 0, 0);
	frontXZ = glm::vec3(0, 0, 0);
	right = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);

	movementSpeed = 0.02;
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
	pitch = std::max(-90 + 0.1, std::min(pitch, 90 - 0.1));
	calculateCameraVectors();
}