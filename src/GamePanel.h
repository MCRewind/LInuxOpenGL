#ifndef __GAMEPANEL_H_
#define __GAMEPANEL_H_

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
		void update(double deltaTime);
		void setActive();
		Vao* vao;
		Shader2t* shader;
		TexRect* texture;
};

#endif
