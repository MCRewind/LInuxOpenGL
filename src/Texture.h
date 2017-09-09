#ifndef TEXTURE
#define TEXTURE

class Texture
{
public:
	Texture(const char* path);
	~Texture();
private:
	GLuint tex;
	int id, width, height;
};

#endif