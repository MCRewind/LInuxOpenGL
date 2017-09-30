#ifndef GAMEPANEL
#define GAMEPANEL

#include "Shader.h"
#include "Vao.h"
#include "Window.h"
#include "Panel.h"
#include "TexRect.h"
#include "Camera.h"

class GamePanel : public Panel
{
	public:
		GamePanel(Window*, Camera*);
		~GamePanel();
		void render();
		void update();
		void setActive();
		Vao* vao;
		Shader2t* shader;
		TexRect* texture;
};

#endif
