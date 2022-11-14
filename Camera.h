#pragma once

// #pragma once 与下面的作用相同 都是当已经有这个.h文件时候，就不去再次汇入了
// #ifndef CAMERA_H   //编号
// .......
// #endif CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);

	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp); //根据角度，生成相机位置

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





