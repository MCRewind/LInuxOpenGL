#ifndef ANIM
#define ANIM

class Anim : public Texture
{
	public:
		Anim(const char* path, int numFrames, int fps);
		~Anim();
		void bind();
		void play();
		void pause();
		int getWidth();
		float getFrameWidth();
		float getOffset();
	private:
		float FRAME_WIDTH;
		long NANO_PER_FRAME;
		int NUM_FRAMES;

		int curFrame;
		long startTime;
		bool playing;
};

#endif
