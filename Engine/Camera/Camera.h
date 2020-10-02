#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>

class Camera {
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);
	void OnDestroy();
	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	void AddLightSources(LightSource* lightsource_);
	std::vector<LightSource*> GetLightSources() const;
	glm::vec3 GetPosition() const;
	glm::vec2 GetClippingPlanes() const;
	glm::vec4 front, back, left, otherLeft, top, bottom;
	void GetFrustum();

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);
private:
	void UpdateCameraVector();
	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	std::vector<LightSource*> lightsources;
};
#endif // !1

