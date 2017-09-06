#include <GLFW/glfw3.h>
#include "Window.h"

int main()
{
	Window* window = new Window(520, 520, "test", true, true);
	while(!window->shouldClose())
	{
		window->update();
		window->clear();
		window->swap();
	}
}
