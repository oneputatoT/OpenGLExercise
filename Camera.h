#pragma once

// #pragma once �������������ͬ ���ǵ��Ѿ������.h�ļ�ʱ�򣬾Ͳ�ȥ�ٴλ�����
// #ifndef CAMERA_H   //���
// .......
// #endif CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);

	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp); //���ݽǶȣ��������λ��

	glm::vec3 Position;
	glm::vec3 Forword;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;

	float Pitch;
	float Yaw;

	float SensitivityX = 0.01f;
	float SensitivityY = 0.01f;

	float SpeedZ = 0;
	float SpeedD = 0;
	float SpeedY = 0;

	glm::mat4 GetViewMatrix();

	glm::mat4 GetViewMatrixTwo();

	void ProcessMouseMove(float deltaX, float deltaY);

	void UpdateCameraPos();

private:
	void UpdateCameraVector();
};





