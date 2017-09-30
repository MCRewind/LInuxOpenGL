#ifndef VAO
#define VAO

#include <GL/glew.h>

class Vao 
{
	public:
		Vao(float vertices[], int num, int indices[], int count);
		void addAttrib(float data[], int length, int size);
		void render();
		~Vao();
	private:
		GLuint vao, ibo, vbos[15];
		int attrib, count;
};

#endif