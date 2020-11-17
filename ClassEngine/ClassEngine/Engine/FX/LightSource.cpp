#include "LightSource.h"



LightSource::LightSource(glm::vec3 position_, glm::vec3 colour_, float ambient_, float diffuse_) {
	position = position_;
	colour = colour_;
	ambient = ambient_;
	diffuse = diffuse_;
}

LightSource::~LightSource() {

}

glm::vec3 LightSource::GetPosition() {
	return position;
}

glm::vec3 LightSource::GetColour() {
	return colour;
}

float *LightSource::GetAmbient() {
	return &ambient;
}

float *LightSource::GetDiffuse() {
	return &diffuse;
}

void LightSource::SetPosition(glm::vec3 position_) {
	position = position_;
}

void LightSource::SetColour(glm::vec3 colour_) {
	colour = colour_;
}

void LightSource::SetAmbient(float ambient_) {
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_) {
	diffuse = diffuse_;
}