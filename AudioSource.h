#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include "../Rendering/3D/AComponent.h"
#include <string>
#include <glm.hpp>

class AudioSource : public AComponent
{
public:
	AudioSource(std::string soundName_, bool loopSound_, bool is3d_, bool howPlay_);
	~AudioSource();

	virtual bool OnCreate(class GameObject* parent_) = 0;
	virtual void Update(float DeltaTime_) = 0;

	bool isPlaying(int channelID_);
	int playSound(std::string soundName_, glm::vec3 pos_, glm::vec3 vel_, float volume);

private:
	int channelID;
	std::string audioName;
};

#endif