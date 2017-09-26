#include "Shader.h"
#include "Texture.h"
#include "Rect.h"

#include "TexRect.h"

glm::mat4 fullTransform()
{
         glm::mat4 temp;
         temp = glm::translate(temp, position);
         temp = glm::rotate<float>(temp, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
         temp = glm::scale(temp, glm::vec3(sx*scale, sy*scale, 1));
         return temp;
}

TexRect::TexRect(Camera* camera, String texPath, float x, float y, float depth, float width, float height)
{
	this->camera = camera;
	if(vao == NULL)
		initVao();
	position = glm::vec3(x, y, depth);
	rotation = 0;
	scale = 1;
	sx = width / dims.x;
	sy = height / dims.y;
	texture = new Texture(texPath);
	shader = new Shader2t();	
}

void TexRect::render()
{
	texture->bind();
	shader->enable();
	shader->setProjection(camera->getProjection());
	shader->setView(camera->getView());
	shader->setModel(fullTransform());
	vao->render();
	shader->disable();
	texture->unbind();
}

void TexRect::setShader(Shader* shader)
{
	this->shader = shader;
}

Shader* TexRect::getShader()
{
	return shader;
}

void TexRect::setTexture(Texture* texture)
{
	this->texture = texture;
}

Texture* TexRect::getTexture()
{
	return texture;
}

TexRect::~TexRect()
{
	
}
