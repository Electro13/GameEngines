#ifndef PARTICLE_H
#define PARTICLE_H

#include <glew.h>
#include <glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"

class Emitter;

struct ParticleVertex {
	glm::vec3 particlePosition;
	glm::vec2 particleTextureCoords;
	ParticleVertex(glm::vec3 position_, glm::vec2 texturecoords_) {
		particlePosition = position_;
		particleTextureCoords = texturecoords_;
	};
};

class Particle
{
public:

	Particle(GLuint shaderProgram_, GLuint textureID_);
	~Particle();

	glm::vec3 GetPosition() { return position; }

	void SetPosition(glm::vec3 position_) { position = position_; }

	glm::vec3 GetColour() { return colour; }

	void SetColour(glm::vec3 colour_) { colour = colour_; }

	glm::vec3 GetVelocity() { return velocity; }

	void SetVelocity(glm::vec3 velocity_) { velocity = velocity_; }

	float GetLifeTime() { return lifeTime; }

	void SetLifeTime(float lifeTime_) { lifeTime = lifeTime_; }

	void Render(Camera* camera_);

private:
	std::vector<ParticleVertex> particleList;
	void GenerateBuffers();
	void SetDistance();
	GLuint VAO, VBO, modelLoc, projLoc, colourLoc, textureLoc, viewLoc;
	GLuint particleShader, textureID;
	glm::vec3 position, velocity, colour;
	float lifeTime, size, angle;
	friend class Emitter;
};

#endif

