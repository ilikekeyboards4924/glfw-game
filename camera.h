#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <algorithm> // for std::min and std::max

class Camera {
public:
	glm::vec3 position;
	double pitch;
	double yaw;

	glm::vec3 front;
	glm::vec3 frontXZ;
	glm::vec3 right;
	glm::vec3 up;

	double movementSpeed;
	Camera();

	void normalizeCameraVectors();

	void calculateCameraVectors();

	void updateCamera();
};

#endif