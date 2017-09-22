#ifndef TEXRECT
#define TEXRECT

class Texrect 
{
	public:
		Texrect(Camera camera, String texPath, float x, float y, float depth, float width, float height);
		~Texrect();
		void render();
		void setShader(Shader shader);
		Shader getShader();
		void setTexture(Texture texture);
		Texture getTexture();
	private:
		Shader* shader;
		Texture* texture;
};

#endif
