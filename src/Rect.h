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
		float getScale();
		void setScale(float scale);
		void setPos(float x, float y);
		void reset(float x, float y, float width, float height);
	protected:
		glm::vec3 dims, position;
		Vao* vao;
		Camera* camera;
		float rotation, sx, sy, scale;
		void initVao();
};

#endif
