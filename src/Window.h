#ifndef __WINDOW_H_
#define __WINDOW_H_

#include <GLFW/glfw3.h>

class Window
{
	public:
		Window(int width, int height, const char* title, bool vsync, bool resizable);
		void init(int width, int height, const char* title, bool vSync, bool resizable);
		~Window();
		void update();
		void clear();
		void swap();
		bool shouldClose();
		void close();
		bool isKeyPressed(int keyCode);
		bool isKeyReleased(int keyCode);
	private:
		GLFWwindow* window;
};

#endif
