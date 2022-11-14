#pragma once

#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);         //实例构造器
	//~Shader();          //结构函数
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;       //Shader Program ID;
	void Use();
	void SetUniform3f(const char* paramNameString, glm::vec3 param);
	void SetUniform1f(const char* paramNameString, float param);
	void SetUniform1i(const char* paramNameString, int slot);

	enum SLOT
	{
		DIFFUSE,
		SPECULAR
	};

private:
	void CheckCompileErrors(unsigned int ID,std::string type);
};

