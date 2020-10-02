#include "PhysicsComponent.h"
#include "GameObject.h"


PhysicsComponent::PhysicsComponent()
{
	parent = nullptr;
}


PhysicsComponent::~PhysicsComponent()
{
	parent = nullptr;
}

void PhysicsComponent::Update(float DeltaTime_) {

}

bool PhysicsComponent::OnCreate(GameObject* parent_) {
	parent = parent_;
	return true;
}