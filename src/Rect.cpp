#include <GL/glew.h>

#include "Rect.h"

Rect::Rect()
{
	dims = glm::vec3(10, 10, 0);
}

Rect::~Rect() 
{
	
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

glm::vec2 Rect::getScale()
{
	return scale;
}

void Rect::setScale(float x, float y)
{
	this->scale.x = x;
	this->scale.y = y;
}

void Rect::zoomi()
{
	scale.x++;
	scale.y++;
}

void Rect::zoomo()
{
	scale.x--;
	scale.y++;
}

void Rect::setPos(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Rect::reset(float x, float y, float width, float height)
{
	position.x = x;
	position.y = y;
	sx = width / dims.x;
	sy = height / dims.y;
}
