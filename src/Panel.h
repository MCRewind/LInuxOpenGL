#ifndef PANEL
#define PANEL

class Panel {
	public:
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void setActive() = 0;
		int getState();
	protected:	
		Window* window;
		Camera* camera;
		int state;
		Panel(Window* window, Camera* camera);
};

#endif
