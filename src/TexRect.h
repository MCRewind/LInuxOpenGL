#ifndef TEXRECT
#define TEXRECT

class TexRect : public  Rect
{
	public:
		TexRect(Camera* camera, String texPath, float x, float y, float depth, float width, float height);
		~TexRect();
		void render();
		void setShader(Shader* shader);
		Shader* getShader();
		void setTexture(Texture* texture);
		Texture* getTexture();
	private:
		Shader* shader;
		Texture* texture;
};

#endif
