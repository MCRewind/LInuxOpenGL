#ifndef __RECT_H_
#define __RECT_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vao.h"
#include "Camera.h"

class Rect 
{
	public:
		Rect();
		~Rect();
		void render();
		void zoomi();
		void zoomo();
		float getWidth();
		float getHeight();
		glm::vec2 getScale();
		void setScale(float x, float y);
		void setPos(float x, float y);
		void reset(float x, float y, float width, float height);
	protected:
		glm::vec3 dims, position;
		glm::vec2 scale;
		Vao* vao;
		Camera* camera;
		float rotation, sx, sy;
		void initVao();
};

#endif
