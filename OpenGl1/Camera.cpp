#include "Camera.h"
#include<glm\gtx\transform.hpp>

Camera::Camera() :viewDirection(0.0f,0.0f,-1.0f),//one unit from where the camera is 
UP(0.0f,1.0f,0.0f)//need not be nomalized
{
}
void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	//in X - plane  ie around UP vector
	
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 50)
	{
		oldMousePosition = newMousePosition;
		return;
	}
	viewDirection = glm::mat3(glm::rotate(mouseDelta.x/25.0f, UP))*viewDirection;
	
	//up-down in the Y plane
	glm::vec3 newRotationAxis = glm::cross(viewDirection,UP);
	viewDirection = glm::mat3(glm::rotate(mouseDelta.y / 25.0f, newRotationAxis))*viewDirection;

	
	oldMousePosition = newMousePosition;
}
glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position+viewDirection, UP);
}

float movement_speed= 0.1f;
void Camera::moveForward()
{
	position += movement_speed*viewDirection;
}
void Camera::moveBackward()
{
	position -= movement_speed*viewDirection;
}
void Camera::strafeLeft()
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	position += movement_speed*strafeDirection;
}
void Camera::strafeRight()
{
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	position += movement_speed*-strafeDirection;
}
void Camera::moveUp()
{
	position += movement_speed*UP;
}
void Camera::moveDown()
{
	position -= movement_speed*UP;
}


