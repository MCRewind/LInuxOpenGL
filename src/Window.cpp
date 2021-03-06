#include <iostream>
#include <GL\glew.h>

#include "Window.h"

void errorCallback(int32 code, const char message[]);
void windowSizeCallback(GLFWwindow * window, int32 width, int32 height);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double x, double y);
void scrollCallback(GLFWwindow* window, double x, double y);

double mouseX, mouseY;
double scrollX, scrollY;
bool mouseLeft, mouseRight;

Window::Window(int32 width, int32 height, const char title[], bool vSync, bool resizable)
{
	init(width, height, title, vSync, resizable);
}

void Window::init(int32 width, int32 height, const char title[], bool vSync, bool resizable)
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initalize GLFW!");
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	if (width < -1 && height < -1)
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (width > 0 && height > 0)
	{
		window = glfwCreateWindow(width, height, title, 0, 0);
		this->width = width;
		this->height = height;
	}
	else if (width < 0 && height < 0)
	{
		window = glfwCreateWindow(vidMode->width, vidMode->height, title, 0, 0);
		this->width = vidMode->width;
		this->height = vidMode->height;
	}
	else
	{
		window = glfwCreateWindow(vidMode->width, vidMode->height, title, glfwGetPrimaryMonitor(), 0);
		this->width = vidMode->width;
		this->height = vidMode->height;
	}

	if (!window)
	{
		fprintf(stderr, "Failed to create window!");
		glfwTerminate();
		exit(-1);
	}
	else if (width > 0 && height > 0)
		glfwSetWindowPos(window, (vidMode->width - width) / 2, (vidMode->height - height) / 2);

	glfwMakeContextCurrent(window);

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW!");
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(-1);
	}

	glfwSwapInterval(vSync);

	glClearColor(0, .5, .5, 1);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetWindowSizeCallback(window, windowSizeCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glfwSetWindowUserPointer(window, this);
}

void Window::poll()
{
	glfwPollEvents();
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap()
{
	glfwSwapBuffers(window);
}

int32 Window::getWidth()
{
	return width;
}

int32 Window::getHeight()
{
	return height;
}

void Window::setWidth(int32 width)
{
	this->width = width;
}

void Window::setHeight(int32 height)
{
	this->height = height;
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::close()
{
	glfwSetWindowShouldClose(window, true);
}

bool Window::isKeyPressed(int32 key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

double Window::getMouseX()
{
	return mouseX;
}

double Window::getMouseY()
{
	return mouseY;
}

double Window::getMouseCX(Camera* camera)
{
	return ((((mouseX * camera->getWidth()) / width) - camera->getPos().x) / camera->getScale());
}

double Window::getMouseCY(Camera* camera)
{
	return ((((mouseY * camera->getHeight()) / height) - camera->getPos().y) / camera->getScale());
}

double Window::getMouseUX(Camera* camera)
{
	return ((mouseX * camera->getWidth()) / width);
}

double Window::getMouseUY(Camera* camera)
{
	return ((mouseY * camera->getHeight()) / height);
}

bool Window::getMouseLeft()
{
	return mouseLeft;
}

bool Window::getMouseRight()
{
	return mouseRight;
}

double Window::getScrollX()
{
	return scrollX;
}

double Window::getScrollY()
{
	return scrollY;
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::terminate()
{
	glfwTerminate();
}

void errorCallback(int32 code, const char message[])
{
	fprintf(stderr, "Error code: %d  -  %s", code, message);
}

void windowSizeCallback(GLFWwindow * window, int32 width, int32 height)
{
	Window * wObj = static_cast<Window *> (glfwGetWindowUserPointer(window));
	glViewport(0, 0, width, height);
	wObj->setWidth(width);
	wObj->setHeight(height);
}

void cursorPosCallback(GLFWwindow* window, double x, double y)
{
	mouseX = x;
	mouseY = y;
}

void scrollCallback(GLFWwindow* window, double x, double y)
{
	scrollX = x;
	scrollY = y;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		mouseRight = true;
	else
		mouseRight = false;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		mouseLeft = true;
	else
		mouseLeft = false;
}
