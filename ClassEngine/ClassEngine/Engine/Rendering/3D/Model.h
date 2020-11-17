#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "LoadOBJModel.h"

class Model {
public:
	Model(const std::string& objFilePath_,
		const std::string& mtlFilePath_,
		GLuint shaderProgram_);
	~Model();
	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);

	int CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_,
		glm::vec3 scale_);
	void UpdateInstance(int index_, glm::vec3 position_, float angle_,
		glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTransform(int index_) const;
	BoundingBox GetBoundingBox();
	GLuint GetShaderProgram() const;

	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modelInstances;
	LoadOBJModel* obj;
	BoundingBox box;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_,
		glm::vec3 scale_) const;
	void LoadModel();

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
};
#endif