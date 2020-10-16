#include "AudioSource.h"
#include "AudioHandler.h"

AudioSource::AudioSource(std::string soundName_, bool loopSound_, bool is3d_, bool howPlay_) {
	channelID = -1;
	audioName = soundName_;
}

AudioSource::~AudioSource() {

}

bool AudioSource::OnCreate(class GameObject* parent_) {
	return true;
}

void AudioSource::Update(float DeltaTime_) {

}

bool AudioSource::isPlaying(int channelID_) {
	return channelID_;
}

int AudioSource::playSound(std::string soundName_, glm::vec3 pos_, glm::vec3 vel_, float volume) {
	return true;
}