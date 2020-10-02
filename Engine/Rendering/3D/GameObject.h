#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Rendering/3D/AComponent.h"

class GameObject {
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	void Render(Camera* camera_);
	void Update(const float deltaTime_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	BoundingBox GetBoundingBox();
	std::string GetTag() const;
	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	template<typename T>
	void AddComponent() {
		T* temp = new T();
		if (dynamic_cast<AComponent*>(temp)) {
			if (GetComponent<T>()) {
				Debug::Error("Failed to add already existing component. Deleting Components", "GameObject.cpp", __LINE__);
				delete temp;
				return;
			}
			else if (GetComponent<T>() == nullptr) {
				component.push_back(temp);
				temp->OnCreate(this);
			}
		}

		else {
			Debug::Error("Object is not a child of component. Deleting Components", "GameObject.cpp", __LINE__);
			delete temp;
			return;
		}
	}

	template<typename D>
	D* GetComponent() {
		for (auto c : component) {
			if (dynamic_cast<D*>(c)) {
				return dynamic_cast<D*>(c);
			}
		}
	}

	template<typename E>
	void RemoveComponent() {
		for (int i = 0; i < 5; i++) {
			if (dynamic_cast<E*>(i)) {
				component = nullptr;
				component.erase(component.begin() + i);
			}
		}
	}

private:
	Model* model;

	std::vector<AComponent*> component;

	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	int modelInstance;

	BoundingBox box;

	std::string tag;

	bool hit;
};
#endif