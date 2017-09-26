#ifndef ANIMRECT
#define ANIMRECT

class AnimRect : public Rect
{
	public:
		AnimRect(Camera* camera, String texPath, int frames, int fps, float x, float y, float depth, float width, float height);
		~AnimRect();
		void render();
		void setShader(Shader* shader);
		Shader* getShader();
		void setAnim(Anim* texture);
		Anim* getAnim();
	private:
		Shader* shader;
		Anim* texture;
};

#endif
