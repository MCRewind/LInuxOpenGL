#include <GLFW/glfw3.h>
#include "Texture.h"

#include "Anim.h"

Anim::Anim(const char* path, int numFrames, int fps) : Texture(path)
{
	FRAME_WIDTH = 1.0f / (float) numFrames;
	NANO_PER_FRAME = 1000000000l / fps;
	curFrame = 0;
	NUM_FRAMES = numFrames;
	startTime = glfwGetTime();
	playing = true;
}

void Anim::bind()
{
	Texture:bind();
	if (playing)
	{
		int frame = (int) ((glfwGetTime() - startTime) / NANO_PER_FRAME);
		curFrame = frame % NUM_FRAMES;
	}
}

void Anim::play()
{
	playing = true;
}

void Anim::pause()
{
	playing = false;
}

int Anim::getWidth()
{
	return getWidth() / NUM_FRAMES;
}

float Anim::getFrameWidth()
{
	return FRAME_WIDTH;
}

float Anim::getOffset()
{
	return FRAME_WIDTH * curFrame;
}

Anim::~Anim() 
{
	
}
