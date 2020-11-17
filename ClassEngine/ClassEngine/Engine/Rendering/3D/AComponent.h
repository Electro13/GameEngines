#ifndef ACOMPONENT_H
#define ACOMPONENT_H

class AComponent
{
public:
	virtual bool OnCreate(class GameObject* parent_) = 0;
	virtual void Update(float DeltaTime_) = 0;

protected:
	GameObject* parent;
};
#endif
