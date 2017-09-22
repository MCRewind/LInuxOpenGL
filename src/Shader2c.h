#ifndef SHADER2C
#define SHADER2C

class Shader2c : Shader 
{
	public:
		int colorLoc;
	protected:
		Shader2c();
		~Shader2c();
		void getUniformLocs(const char* name);
		void setColor(float r, float g, float b, float a);
};

#endif
