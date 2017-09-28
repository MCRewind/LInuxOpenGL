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
#include "Rect.h"
#include "TexRect.h"
#include "ResourceManager.cpp"
#include "Panel.h"
#include "GamePanel.h"

int map[5][5] =
{
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 1, 0, 1, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 0, 0
};

GamePanel::GamePanel(Window* window, Camera* camera) : Panel(window, camera)
{
	state = 0;

	tex0 = new Texture("res/textures/test.png");
	tex1 = new Texture("res/textures/cmbt.png");
	texture = new TexRect(camera, "res/textures/test.png", 100, 100, 0, 16, 16);
}

void GamePanel::update()
{
	
}

void GamePanel::render()
{
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			texture->setPos(i * 16, j * 16);
			if (map[i][j] == 0)
				texture->setTexture(getTexture(0));
			else if (map[i][j] == 1)
				texture->setTexture(gettexture(0));
			texture->render();
		}
}

void GamePanel::setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
	delete texture;
}
