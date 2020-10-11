#ifndef GUIIMAGECOMPONENT_H
#define GUIIMAGECOMPONENT_H

#include <glew.h>
#include <glm/glm.hpp>
#include <string>
#include "Engine/Camera/Camera.h"
#include "GUIObject.h"
#include "SpriteSurface.h"
#include "GUIComponent.h"

class GUIImageComponent : public GUIComponent
{
public:
    GUIImageComponent();
  virtual ~GUIImageComponent();

    virtual bool OnCreate(std::string imageName_, glm::vec2 offset_, glm::vec2 guiScale_, float guiAngle_, glm::vec4 guiTint_);

    virtual void Draw(Camera* cam_, glm::vec2 position_);

    virtual void FindContainingPoint();

private:

    SpriteSurface* sprite;
    glm::vec2 offset;

};


#endif // !GUIIMAGECOMPONENT_H