#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Shader.h"

class Material
{
public:
	Material(Shader* _shader,glm::vec3 _ambient, unsigned int _diffuse, unsigned int _specular,float _shininess);
	Shader* shader;
	glm::vec3 ambient;
	unsigned int diffuse;
	unsigned int specular;
	float shininess;

};

