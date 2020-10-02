#include "GameObject.h"

GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr){
	model = model_;
	position = position_;
	angle = 0.0f;
	rotation = glm::vec3(0.0f, 3.0f, 0.0f);
	scale = glm::vec3(1.0f);
	tag = "";
	hit = false;
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		box = model->GetBoundingBox();
		box.transform = model->GetTransform(modelInstance);
	}
}

GameObject::~GameObject() {
	model = nullptr;
}

void GameObject::Render(Camera* camera_) {
	if (model) {
		model->Render(camera_);
	}
}

void GameObject::Update(const float deltaTime_) {
	SetAngle(angle + 0.005);
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

glm::vec3 GameObject::GetPosition() const {
	return position;
}

float GameObject::GetAngle() const {
	return angle;
}

glm::vec3 GameObject::GetRotation() const {
	return rotation;
}

glm::vec3 GameObject::GetScale() const {
	return scale;
}

BoundingBox GameObject::GetBoundingBox() {
	return box;
}

std::string GameObject::GetTag() const {
	return tag;
}

bool GameObject::GetHit() const {
	return hit;
}

void GameObject::SetPosition(glm::vec3 position_) {
	position = position_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_) {
	angle = angle_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_) {
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_) {
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
		box.minVert *= scale.x > 1.0f ? 1.0f : (scale.x / 2.0f);
		box.maxVert *= scale.x > 1.0f ? 1.0f : (scale.x / 2.0f);
	}
}

void GameObject::SetTag(std::string tag_) {
	tag = tag_;
}

void GameObject::SetHit(bool hit_, int buttonType_) {
	hit = hit_;
	if (hit) {
		std::cout << tag << " was hit" << std::endl;
	}
}