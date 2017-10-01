#ifndef __PANEL_H_
#define __PANEL_H_

#include "Window.h"
#include "Camera.h"

class Panel {
	public:
		virtual void update(double deltaTime) = 0;
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
