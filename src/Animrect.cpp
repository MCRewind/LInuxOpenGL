#include "Animrect.h"

glm::mat4 fullTransform()
{
         glm::mat4 temp;
         temp = glm::translate(temp, position);
         temp = glm::rotate<float>(temp, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
         temp = glm::scale(temp, glm::vec3(sx*scale, sy*scale, 1));
         return temp;
}
Animerect::Animrect(Camera camera, String texPath, int frames, int fps, float x, float y, float depth, float width, float height)
{
	this->camera = camera;
	if(vao == NULL)
		initVao();
	position = glm::vec3(x, y, depth);
	rotation = 0;
	scale = 1;
	sx = width / dims.x;
	sy = height / dims.y;
	texture = new Anim(texPath, frames, fps);
	shader = new Shader2a();
}

void Texrect::render()
{
	texture->bind();
	shader->enable();
	shader->setProjection(camera->getProjection());
	shader->setView(camera->getView());
	shader->setModel(fullTransform());
	(Shader2a) shader->setAnim(texture);
	vao->render();
	shader->disable();
	texture->unbind();
}

void Animrect::setShader(Shader* shader)
{
	this->shader = shader;
}

Shader Animrect::getShader()
{
	return shader;
}

void Animrect::setAnim(Anim texture)
{
	this->texture = texture;
}

Anim Animrect::getAnim()
{
	return texture;
}

Texrect::~Texrect()
{
	
}
