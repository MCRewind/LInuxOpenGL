#ifndef TEXRECT
#define TEXRECT

class TexRect : public Rect
{
	public:
		TexRect(Camera* camera, const char* texPath, float x, float y, float depth, float width, float height);
		~TexRect();
		void render();
		void setShader(Shader2t* shader);
		Shader2t* getShader();
		void setTexture(Texture* texture);
		Texture* getTexture();
		glm::mat4 fullTransform();
	private:
		Shader2t* shader;
		Texture* texture;
};

#endif
