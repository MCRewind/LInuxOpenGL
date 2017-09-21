#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Camera.h"

Camera::Camera(int width, int height)
{
	rotation = 0;
	setDims(width, height);
	setPos(glm::vec3(0, 0, 0));
}

Camera::~Camera()
{

}

void Camera::setDims(int width, int height)
{
	//projection = glm::perspective<float>(glm::radians(45.0f), width / height, 1.0f, 10.0f);
	this->width = width;
	this->height = height;
	std::cout << width << ", " << height << std::endl;
	projection = glm::ortho(0.0f, (float) width, (float) height, 0.0f, 0.0f, 1.0f);
	//projection = glm::ortho(-10.0f, 0, 0, 10.0f, 0.0f, 100.0f);                     
}

void Camera::translate(glm::vec3 vec)
{
	position.x -= vec.x;
	position.y -= vec.y;
	position.z -= vec.z;
}

glm::vec3 Camera::getPos()
{
	return position;
}

void Camera::setPos(glm::vec3 vec)
{
	position.x = -vec.x;
	position.y = -vec.y;
	position.z = -vec.z;
}

float Camera::getRotation()
{
	return -rotation;
}

void Camera::rotate(float angle)
{
	rotation -= angle;
}

void Camera::setRotation(float angle)
{
	rotation = -angle;
}

glm::mat4 Camera::getProjection()
{
	return projection;
}

glm::mat4 Camera::getView()
{
	glm::mat4 temp;
	temp = glm::rotate(temp, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	temp = glm::translate(temp, position);

	return temp;
}
