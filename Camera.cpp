#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	Position = position;

	Forword = glm::normalize(target - position);   //设定Forword向量 作为Z方向
	
	WorldUp = glm::normalize(worldUp);

	Right = glm::normalize(glm::cross(WorldUp, Forword));   //叉乘出垂直与这两条向量组成的面的向量，作为Camera的Right

	Up = glm::normalize(glm::cross(Forword, Right));    //叉乘出Camera的Up向量
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp)
{
	Position = position;
	WorldUp = worldUp;

	Pitch = pitch;
	Yaw = yaw;

	Forword.y = glm::sin(Pitch);
	Forword.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forword.z = glm::cos(Pitch) * glm::cos(Yaw);

	Forword = glm::normalize(Forword);

	Right = glm::normalize(glm::cross(WorldUp, Forword));

	Up = glm::normalize(glm::cross(Forword, Right));

	Forword = -glm::normalize(Forword);
}


glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forword, WorldUp); //返回一个ViewMartix，第一个参数为Camera当前位置，第二个为观察点，第三个为世界的向上方向
}


void Camera::UpdateCameraVector()
{
	Forword.y = glm::sin(Pitch);
	Forword.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forword.z = glm::cos(Pitch) * glm::cos(Yaw);

	Forword = glm::normalize(Forword);

	Right = glm::normalize(glm::cross(WorldUp, Forword));

	Up = glm::normalize(glm::cross(Forword, Right));

	Forword = -glm::normalize(Forword);
}

void Camera::ProcessMouseMove(float deltaX, float deltaY)
{
	Pitch += glm::radians(deltaY)* SensitivityY;
	Yaw -= glm::radians(deltaX)* SensitivityX;

	if (Pitch >= glm::radians(90.0f))
	{
		Pitch = glm::radians(89.0f);
	}

	if (Pitch <= glm::radians (-90.0f))
	{
		Pitch = glm::radians (-89.0f);
	}

	UpdateCameraVector();
}

void Camera::UpdateCameraPos()
{
	Position += Forword * SpeedZ * 0.1f;
	Position += Right * SpeedD * 0.1f;
	Position += Up * SpeedY * 0.1f;
}

