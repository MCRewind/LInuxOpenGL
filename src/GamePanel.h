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
		Shader* shader;
		Texture* texture;	
};

#endif
