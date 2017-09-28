#ifndef GAMEPANEL
#define GAMEPANEL

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
		Texture* tex0, *tex1;
};

#endif
