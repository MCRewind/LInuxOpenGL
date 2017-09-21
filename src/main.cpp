#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Window.h"
#include "Vao.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include <iostream>

#include <stdio.h>

glm::mat4 fullTransform()
{
	glm::mat4 temp;
	temp = glm::translate(temp, glm::vec3(0, 0, 0));
	temp = glm::rotate<float>(temp, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	temp = glm::scale(temp, glm::vec3(1, 1, 1));
	return temp;
}

int main()
{
	Window* window = new Window(520, 520, "test", true, true);

	float vertices[] = {
		0, 50, 0,
 		50, 50, 0,
 		50, 0, 0,
		0,  0, 0
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
	Vao* vao = new Vao(vertices, 4, indices, 6);

	vao->addAttrib(texCoords, 4, 2);

	Shader* shader = new Shader("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");

	Texture* texture = new Texture("res/textures/test.png");

	Camera* camera = new Camera(520, 520);
	
	glm::vec4 kek = camera->getProjection() * camera->getView() * fullTransform() * glm::vec4(0, 500, 0, 1);

	std::cout << glm::to_string(kek) << std::endl;
	std::cout << glm::to_string(camera->getProjection());

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while (!window->shouldClose())
	{
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0)
		{
			//printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}
		window->update();
		window->clear();
		texture->bind();
		shader->enable();
		shader->setProjection(camera->getProjection());
		shader->setView(camera->getView());
		shader->setModel(fullTransform());
		vao->render();
		shader->disable();
		texture->unbind();
		window->swap();
		if (window->isKeyPressed(GLFW_KEY_ESCAPE))
			window->close();
	}
	delete window;
	delete vao;
	delete texture;
	delete camera;
}
