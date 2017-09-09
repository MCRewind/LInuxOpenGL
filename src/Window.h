#ifndef WINDOW
#define WINDOW

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
	private:
		GLFWwindow* window;
};

#endif
