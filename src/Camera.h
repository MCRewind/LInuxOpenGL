#ifndef CAMERA
#define CAMERA

class Camera
{
public:
	Camera();
	~Camera();
	setDims();
private:
	float width, height, rotation;
	glm::mat4 projection;
	glm::vec3 position;
};

#endif 