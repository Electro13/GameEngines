#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H
#include <glm/glm.hpp>
class LightSource
{
public:
	LightSource(glm::vec3 position_, glm::vec3 colour_, float ambient_, float diffuse_);
	~LightSource();

	glm::vec3 GetPosition();
	glm::vec3 GetColour();
	float* GetAmbient();
	float* GetDiffuse();
	void SetPosition(glm::vec3 position_);
	void SetColour(glm::vec3 colour_);
	void SetAmbient(float ambient_);
	void SetDiffuse(float diffuse_);
private:
	glm::vec3 position;
	glm::vec3 colour;
	float ambient;
	float diffuse;
};
#endif
