#include "Camera.h"
#include<glm\gtx\transform.hpp>

Camera::Camera() :viewDirection(0.0f,0.0f,-1.0f),//one unit from where the camera is 
UP(0.0f,1.0f,0.0f)//need not be nomalized
{
}
glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position+viewDirection, UP);
}



