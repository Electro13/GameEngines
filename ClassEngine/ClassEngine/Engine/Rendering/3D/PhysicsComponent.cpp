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
	//std::cout << "Updating Component" << std::endl;
}

bool PhysicsComponent::OnCreate(GameObject* parent_) {
	parent = parent_;
	return true;
}