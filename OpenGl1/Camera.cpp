#include "Camera.h"
#include<glm\gtx\transform.hpp>

Camera::Camera() :viewDirection(0.0f,0.0f,-1.0f),//one unit from where the camera is 
UP(0.0f,1.0f,0.0f)//need not be nomalized
{
}
void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	viewDirection = glm::mat3(glm::rotate(mouseDelta.x/25.0f, UP))*viewDirection;
	oldMousePosition = newMousePosition;
}
glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position+viewDirection, UP);
}



