#include "TexRect.h"
#include "Panel.h"

#include "GamePanel.h"

GamePanel::GamePanel(Window* window, Camera* camera)
{
	Panel:(window, camera);
	state = 0;
	//texture = new TexRect(camera, "res/textures/test.png", 0, 0, 0, 16, 16); 
}

virtual void GamePanel::~update()
{
	//texture->update();	
}

virtual void render()
{
	//texture->render();
}

virtual void setActive()
{
	state = 0;
}

GamePanel::~GamePanel() {
	
}
