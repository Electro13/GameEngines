#include "GUIObject.h"

GUIObject::GUIObject(glm::vec2 position_) {
	position = position_;
}

GUIObject::~GUIObject() {

}

void GUIObject::Draw(Camera* camera_) {

}

void GUIObject::SetTag(std::string tag_) {
	tag = tag_;
}