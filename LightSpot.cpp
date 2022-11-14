#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angle, glm::vec3 _color):
	position(_position),
	angle(_angle),
	color(_color)
{
	UpdateAngle();
}

void LightSpot::UpdateAngle()
{
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angle.z);
	direction = glm::rotateX(direction, angle.x);
	direction = glm::rotateY(direction, angle.y);
	direction = -direction;
}
