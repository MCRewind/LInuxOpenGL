
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Panel.h"

Panel::Panel(Window* window, Camera* camera) {
	this->window = window;
	this->camera = camera;
}

int Panel::getState()
{
	return state;
}
