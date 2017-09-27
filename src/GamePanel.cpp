#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>

#include "Vao.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "Camera.h"
#include "Panel.h"
#include "GamePanel.h"

	float vertices[12] = {
		0, 150, 0,
 		150, 150, 0,
 		150, 0, 0,
		0,  0, 0
	};
	int indices[6] = {
		0, 1, 3,
		3, 1, 2
	};
	float texCoords[8] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

glm::mat4 fullTransform()
{
	glm::mat4 temp;
	temp = glm::translate(temp, glm::vec3(0, 0, 0));
	temp = glm::rotate<float>(temp, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	temp = glm::scale(temp, glm::vec3(1, 1, 1));
	return temp;
}	

GamePanel::GamePanel(Window* window, Camera* camera) : Panel(window, camera)
{
	state = 0;

	vao = new Vao(vertices, 4, indices, 6);

	vao->addAttrib(texCoords, 4, 2);

	shader = new Shader2t();

	texture = new Texture("res/textures/test.png");
}

void GamePanel::update()
{
	
}

void GamePanel::render()
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

void GamePanel::setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
	delete vao;
	delete shader;
	delete texture;
}
