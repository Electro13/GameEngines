#include "Camera.h"

#include "../Core/CoreEngine.h"

Camera::Camera() : position(glm::vec3()) {
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView, 
		CoreEngine::GetInstance()->GetWindowSize().x /
		CoreEngine::GetInstance()->GetWindowSize().y,
		nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x,
		0.0f, CoreEngine::GetInstance()->GetWindowSize().y,
		-1.0f, 1.0f);

	UpdateCameraVector();
}

Camera::~Camera() {
	OnDestroy();
}

void Camera::SetPosition(glm::vec3 position_) {
	position = position_;
}

void Camera::SetRotation(float yaw_, float pitch_) {
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

glm::mat4 Camera::GetView() const {
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPerspective() const {
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const {
	return orthographic;
}

glm::vec2 Camera::GetClippingPlanes() const {
	return glm::vec2(nearPlane, farPlane);
}

void Camera::UpdateCameraVector() {
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));
}

void Camera::OnDestroy() {
	lightsources.clear();
}

void Camera::AddLightSources(LightSource* lightsource_) {
	lightsources.push_back(lightsource_);
}

std::vector<LightSource*> Camera::GetLightSources() const {
	return lightsources;
}

glm::vec3 Camera::GetPosition() const {
	return position;
}

glm::vec3 Camera::GetForward()
{
	return forward;
}

glm::vec3 Camera::GetUp()
{
	return up;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_) {
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw < 0.0f) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(int y_) {
	if (y_ < 0 || y_ > 0) {
		position += static_cast<float>(y_) * (forward * 2.0f);
	}
	UpdateCameraVector();
}

void Camera::GetFrustum() {
	glm::mat4 viewMatrix = GetView(); // This will hold our viewMatrix
	glm::mat4 projectionMatrix = GetPerspective(); // This will hold our projectionMatrix

	// Empties the vectors
	top = glm::vec4(0); // This is the top of the frustum
	bottom = glm::vec4(0); // This is the bottom of the frustum
	left = glm::vec4(0); // this is the left side of the frustum
	back = glm::vec4(0); // this is the back of the frustum
	front = glm::vec4(0); // this is the front of the frustum
	otherLeft = glm::vec4(0); // this is the right side of the frustum

	// We get our clipping planes simply by combining our viewMatrix and our projectionMatrix by multiplying them
	double clip[4][4];
	clip[0][0] = viewMatrix[0][0] * projectionMatrix[0][0] + viewMatrix[0][1] * projectionMatrix[1][0] + viewMatrix[0][2] * projectionMatrix[2][0] + viewMatrix[0][3] * projectionMatrix[3][0];
	clip[0][1] = viewMatrix[0][0] * projectionMatrix[0][1] + viewMatrix[0][1] * projectionMatrix[1][1] + viewMatrix[0][2] * projectionMatrix[2][1] + viewMatrix[0][3] * projectionMatrix[3][1];
	clip[0][2] = viewMatrix[0][0] * projectionMatrix[0][2] + viewMatrix[0][1] * projectionMatrix[1][2] + viewMatrix[0][2] * projectionMatrix[2][2] + viewMatrix[0][3] * projectionMatrix[3][2];
	clip[0][3] = viewMatrix[0][0] * projectionMatrix[0][3] + viewMatrix[0][1] * projectionMatrix[1][3] + viewMatrix[0][2] * projectionMatrix[2][3] + viewMatrix[0][3] * projectionMatrix[3][3];

	clip[1][0] = viewMatrix[1][0] * projectionMatrix[0][0] + viewMatrix[1][1] * projectionMatrix[1][0] + viewMatrix[1][2] * projectionMatrix[2][0] + viewMatrix[1][3] * projectionMatrix[3][0];
	clip[1][1] = viewMatrix[1][0] * projectionMatrix[0][1] + viewMatrix[1][1] * projectionMatrix[1][1] + viewMatrix[1][2] * projectionMatrix[2][1] + viewMatrix[1][3] * projectionMatrix[3][1];
	clip[1][2] = viewMatrix[1][0] * projectionMatrix[0][2] + viewMatrix[1][1] * projectionMatrix[1][2] + viewMatrix[1][2] * projectionMatrix[2][2] + viewMatrix[1][3] * projectionMatrix[3][2];
	clip[1][3] = viewMatrix[1][0] * projectionMatrix[0][3] + viewMatrix[1][1] * projectionMatrix[1][3] + viewMatrix[1][2] * projectionMatrix[2][3] + viewMatrix[1][3] * projectionMatrix[3][3];

	clip[2][0] = viewMatrix[2][0] * projectionMatrix[0][0] + viewMatrix[2][1] * projectionMatrix[1][0] + viewMatrix[2][2] * projectionMatrix[2][0] + viewMatrix[2][3] * projectionMatrix[3][0];
	clip[2][1] = viewMatrix[2][0] * projectionMatrix[0][1] + viewMatrix[2][1] * projectionMatrix[1][1] + viewMatrix[2][2] * projectionMatrix[2][1] + viewMatrix[2][3] * projectionMatrix[3][1];
	clip[2][2] = viewMatrix[2][0] * projectionMatrix[0][2] + viewMatrix[2][1] * projectionMatrix[1][2] + viewMatrix[2][2] * projectionMatrix[2][2] + viewMatrix[2][3] * projectionMatrix[3][2];
	clip[2][3] = viewMatrix[2][0] * projectionMatrix[0][3] + viewMatrix[2][1] * projectionMatrix[1][3] + viewMatrix[2][2] * projectionMatrix[2][3] + viewMatrix[2][3] * projectionMatrix[3][3];

	clip[3][0] = viewMatrix[3][0] * projectionMatrix[0][0] + viewMatrix[3][1] * projectionMatrix[1][0] + viewMatrix[3][2] * projectionMatrix[2][0] + viewMatrix[3][3] * projectionMatrix[3][0];
	clip[3][1] = viewMatrix[3][0] * projectionMatrix[0][1] + viewMatrix[3][1] * projectionMatrix[1][1] + viewMatrix[3][2] * projectionMatrix[2][1] + viewMatrix[3][3] * projectionMatrix[3][1];
	clip[3][2] = viewMatrix[3][0] * projectionMatrix[0][2] + viewMatrix[3][1] * projectionMatrix[1][2] + viewMatrix[3][2] * projectionMatrix[2][2] + viewMatrix[3][3] * projectionMatrix[3][2];
	clip[3][3] = viewMatrix[3][0] * projectionMatrix[0][3] + viewMatrix[3][1] * projectionMatrix[1][3] + viewMatrix[3][2] * projectionMatrix[2][3] + viewMatrix[3][3] * projectionMatrix[3][3];

	// In order to get the sides of the frustum, we take the clipping planes we received above and extract the sides from them.
	// This code will extract the right side of the frustum
	otherLeft.x = clip[0][3] - clip[0][0];
	otherLeft.y = clip[1][3] - clip[1][0];
	otherLeft.z = clip[2][3] - clip[2][0];
	otherLeft.w = clip[3][3] - clip[3][0];
	// Normalizes the right side of the frustum
	glm::normalize(otherLeft);

	// This code will extract the left side of the frustum
	left.x = clip[0][3] + clip[0][0];
	left.y = clip[1][3] + clip[1][0];
	left.z = clip[2][3] + clip[2][0];
	left.w = clip[3][3] + clip[3][0];
	// Normalizes the left side of the frustum
	glm::normalize(left);

	// This code will extract the bottom of the frustum
	bottom.x = clip[0][3] + clip[0][1];
	bottom.y = clip[1][3] + clip[1][1];
	bottom.z = clip[2][3] + clip[2][1];
	bottom.w = clip[3][3] + clip[3][1];
	// Normalizes the bottom of the frustum
	glm::normalize(bottom);

	// This code will extract the top of the frustum
	top.x = clip[0][3] - clip[0][1];
	top.y = clip[1][3] - clip[1][1];
	top.z = clip[2][3] - clip[2][1];
	top.w = clip[3][3] - clip[3][1];
	// Normalizes the top of the frustum
	glm::normalize(top);

	// This code will extract the front end of the frustum
	front.x = clip[0][3] - clip[0][2];
	front.y = clip[1][3] - clip[1][2];
	front.z = clip[2][3] - clip[2][2];
	front.w = clip[3][3] - clip[3][2];
	// Normalizes the front end of the frustum
	glm::normalize(front);

	// This code will extract the back end of the frustum
	back.x = clip[0][3] + clip[0][2];
	back.y = clip[1][3] + clip[1][2];
	back.z = clip[2][3] + clip[2][2];
	back.w = clip[3][3] + clip[3][2];
	// Normalizes the back end of the frustum
	glm::normalize(back);
}