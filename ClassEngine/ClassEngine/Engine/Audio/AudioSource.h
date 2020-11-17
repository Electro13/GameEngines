#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include "../Rendering/3D/AComponent.h"
#include <string>
#include <glm.hpp>
#include "../Rendering/3D/GameObject.h"

class AudioSource : public AComponent
{
public:
	AudioSource(std::string soundName_, bool loopSound_, bool is3d_, bool howPlay_);
	~AudioSource();

	virtual bool OnCreate(class GameObject* parent_) override;
	virtual void Update(float DeltaTime_) override;

	bool isPlaying();
	void playSound(float volume);

private:
	int channelID;
	std::string audioName;
};

#endif