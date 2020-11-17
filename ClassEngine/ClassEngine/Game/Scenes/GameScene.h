#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Rendering/3D/AComponent.h"
#include "../../Engine/Core/CoreEngine.h"
#include "../../Engine/Graphics/ShaderHandler.h"
#include "../../Engine/Graphics/TextureHandler.h"
#include <glm/gtx/string_cast.hpp>
#include "../../Engine/Audio/AudioHandler.h"
#include "../../Engine/FX/Particle System/Emitter.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void Draw();
private:
	Emitter* emitter;
};
#endif
