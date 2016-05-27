#pragma once
#include<glm\glm.hpp>
class Camera
{
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec2 oldMousePosition;

	const glm::vec3 UP;
public:
	Camera();
	void mouseUpdate(const glm::vec2& newMousePosition);
	glm::mat4 getWorldToViewMatrix() const;
	void moveForward();
	void moveBackward();
	void strafeLeft();
	void strafeRight();
	void moveUp();
	void moveDown();
	
};

