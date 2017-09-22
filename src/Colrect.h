#ifndef COLRECT
#define COLRECT

class Colrect : Rect {
	public:
		Colrect(Camera* camera, float x, float y, float depth, float width, float height, float r, float g, float b, float a);
		~Colrect();
		void render();
	private:
		Shader2c* shader;
		float r, g, b, a;
};

#endif
