#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


Shader::Shader(const char* vertexPath,const char* fragmentPath)
{
	std::ifstream vertexFile;          //声明VertexShader的文件流
	std::ifstream fragmentFile;         //声明FragmentShader的文件流
	std::stringstream vertexSStream;        //声明字符串流
	std::stringstream fragmentSStream;

	vertexFile.open(vertexPath);            //打开路径文件
	fragmentFile.open(fragmentPath);

	//检测坏档
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("Open File error");      //打不开抛出异常
		}

		vertexSStream << vertexFile.rdbuf();     //将File文件流的数据 作为String类型读取进 String流
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();     //将String流转化为String类型
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();        //将String类型转化为Char*(Char数组)
		fragmentSource = fragmentString.c_str();

		//std::printf(vertexSource);
		//std::printf(fragmentSource);

		unsigned int vertex, fragment; //创建   顶点着色器 的ID 河 片元着色器的ID

		vertex = glCreateShader(GL_VERTEX_SHADER);       
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		CheckCompileErrors(ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	catch (const std::exception& ex)
	{
		std::cout<<ex.what()<<std::endl;       //打印异常信息
	}
}

void Shader::Use()
{
	glUseProgram(ID);
}


void Shader::CheckCompileErrors(unsigned int ID, std::string type)
{
	int success;     //判断返回是否成功
	char info[512];      //返回错误信息的储存地址

	if (type != "PROGRAM")       //如果不是ShaderProgram
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);  //检测Shader中有无编译错误      
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, info);            
			std::cout << "ERROR Compile of type:" << type << "\n" << info << "\n";
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);        //检测ShaderProgram中有无编译错误 
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, info);
			std::cout << "ERROR Link of type:" << type << "\n" << info << "\n";
		}
	}

}

void Shader::SetUniform3f(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);
}

void Shader::SetUniform1f(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::SetUniform1i(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
}





