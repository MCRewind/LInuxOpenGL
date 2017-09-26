#ifndef COLRECT
#define COLRECT

class ColRect : Rect {
	public:
		ColRect(Camera* camera, float x, float y, float depth, float width, float height, float r, float g, float b, float a);
		~ColRect();
		void render();
	private:
		Shader2c* shader;
		float r, g, b, a;
};

#endif
