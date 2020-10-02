#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H
#include "AComponent.h"
class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent();
	~PhysicsComponent();
	virtual bool OnCreate(class GameObject* parent_) override;
	virtual void Update(float DeltaTime_) override;
};
#endif
