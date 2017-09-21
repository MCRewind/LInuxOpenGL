#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"

void errorCallback(int errorCode, const char* errorMessage);

Window::Window(int width, int height, const char* title, bool vSync, bool resizable)
{
	init(width, height, title, vSync, resizable);
}

void Window::init(int width, int height, const char* title, bool vSync, bool resizable)
{
	if (!glfwInit())
	{
		fprintf(stderr, "%s", "GLFW failed to initialize\n");
		exit(-1);
	}	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (width == 0 || height == 0 || width >= vidMode->width || height >= vidMode->height)
	{
		width = vidMode->width;
		height = vidMode->height;	
		window = glfwCreateWindow(width, height, "", glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwSetWindowPos(window, (vidMode->width - width) / 2, (vidMode->height - height) / 2);
	}
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		exit(-1);
	}
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
}

void Window::update()
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

bool Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::close() {
	glfwSetWindowShouldClose(window, true);
}

bool Window::isKeyPressed(int keyCode)
{
	return glfwGetKey(window, keyCode) == GLFW_PRESS;
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void errorCallback(int errorCode, const char* errorMessage)
{
	fprintf(stderr, "error: %d: %s", errorCode, errorMessage);
}

