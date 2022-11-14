#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/rotate_vector.hpp>

class LightDirectional
{
public:
	LightDirectional(glm::vec3 _position,glm::vec3 _angle,glm::vec3 _color=glm::vec3(1.0f,1.0f,1.0f));
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 angle;

	void UpdateAngle();


};

