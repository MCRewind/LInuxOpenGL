#ifndef RECT
#define RECT

class Rect {
	public:
		Rect();
		~Rect();
		void render();
		float getWidth();
		float getHeight();
		float getScale();
		void setScale(float scale);
		void reset(float x, float y, float width, float height);
	protected:
		glm::vec3 dims, position;
		Vao* vao;
		Camera* camera;
		float rotation, sx, sy, scale;
		void initVao();
};

#endif
