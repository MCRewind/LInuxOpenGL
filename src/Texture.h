#ifndef TEXTURE
#define TEXTURE

class Texture
{
	public:
		Texture(const char* path);
		~Texture();
		void bind();
		void unbind();
	private:
		GLuint tex;
		int id, width, height;
};

#endif