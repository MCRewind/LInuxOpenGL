#ifndef PANEL
#define PANEL

class Panel {
	public
		virtual void update();
		virtual void render();
		virtual void setActive();
		int getState();
	protected:
		Window* window;
		Camera* camera;
		int state;
		Panel(Window* window, Camera* camera);
		~Panel();
};

#endif
