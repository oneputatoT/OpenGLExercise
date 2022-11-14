#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


Shader::Shader(const char* vertexPath,const char* fragmentPath)
{
	std::ifstream vertexFile;          //����VertexShader���ļ���
	std::ifstream fragmentFile;         //����FragmentShader���ļ���
	std::stringstream vertexSStream;        //�����ַ�����
	std::stringstream fragmentSStream;

	vertexFile.open(vertexPath);            //��·���ļ�
	fragmentFile.open(fragmentPath);

	//��⻵��
	vertexFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("Open File error");      //�򲻿��׳��쳣
		}

		vertexSStream << vertexFile.rdbuf();     //��File�ļ��������� ��ΪString���Ͷ�ȡ�� String��
		fragmentSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();     //��String��ת��ΪString����
		fragmentString = fragmentSStream.str();

		vertexSource = vertexString.c_str();        //��String����ת��ΪChar*(Char����)
		fragmentSource = fragmentString.c_str();

		//std::printf(vertexSource);
		//std::printf(fragmentSource);

		unsigned int vertex, fragment; //����   ������ɫ�� ��ID �� ƬԪ��ɫ����ID

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
		std::cout<<ex.what()<<std::endl;       //��ӡ�쳣��Ϣ
	}
}

void Shader::Use()
{
	glUseProgram(ID);
}


void Shader::CheckCompileErrors(unsigned int ID, std::string type)
{
	int success;     //�жϷ����Ƿ�ɹ�
	char info[512];      //���ش�����Ϣ�Ĵ����ַ

	if (type != "PROGRAM")       //�������ShaderProgram
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);  //���Shader�����ޱ������      
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, info);            
			std::cout << "ERROR Compile of type:" << type << "\n" << info << "\n";
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);        //���ShaderProgram�����ޱ������ 
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





