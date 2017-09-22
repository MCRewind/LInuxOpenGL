#include "Colrect.h"

glm::mat4 fullTransform()
{
         glm::mat4 temp;
         temp = glm::translate(temp, position);
         temp = glm::rotate<float>(temp, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
         temp = glm::scale(temp, glm::vec3(sx, sy, 1));
         return temp;
}


Colrect::Colrect(Camera camera, float x, float y, float depth, float width, float height, float r, float g, float b, float a) 
{
	this->camera = camera;
	if (vao == NULL)
		initVao();
	position = glm::vec3(x, y, depth);
	rotation = 0;
	sx = width / dims.x;
	sy = height / dims.y;
	shader = Shader2c;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Colrect::render()
{
	shader->enable();
	shader->setProjection(camera->getProjection());
	shader->setView(camera->getView());
	shader->setModel(fullTransform());
	shader->setColor(r, g, b, a);
	vao->render();
	shader->disable();
}

Colrect::~Colrect() {
	
}
