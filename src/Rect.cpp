#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

#include "Vao.h"
#include "Camera.h"

#include "Rect.h"

Rect::Rect() {
	dims = glm::vec3(10, 10, 0);
}

Rect::~Rect() {
	
}

void Rect::initVao()
{
	float vertices[] = {
       		 0,      dims.y, 0,
                 dims.x, dims.y, 0,
                 dims.x, 0,      0,
                 0,      0,      0
        };
        int indices[] = {
                 0, 1, 3,
                 3, 1, 2
        };
        float texCoords[] = {
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
        };
	vao = new Vao(vertices, 4, indices, 6);
	vao->addAttrib(texCoords, 4,  2);
}

float Rect::getWidth()
{
	return sx * dims.x;
}

float Rect::getHeight()
{
	return sy * dims.y;
}

float Rect::getScale()
{
	return scale;
}

void Rect::setScale(float scale)
{
	this->scale = scale;
}

void Rect::reset(float x, float y, float width, float height)
{
	position.x = x;
	position.y = y;
	sx = width / dims.x;
	sy = height / dims.y;
}
