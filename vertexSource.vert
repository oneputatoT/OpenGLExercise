#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 5) in vec3 aNormal;
layout(location = 6) in vec2 aTexCoord;


uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 vieMat;
uniform mat4 projMat;

//out vec4 textColor;	
out vec2 TexCord;
out vec3 Normal;
out vec3 FragPos;

void main()
{											 
	//textColor	= vec4(aColor.x,aColor.y,aColor.z,1.0f);
	//TexCord = aTexCoord;
	gl_Position = projMat * vieMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);

	FragPos = (modelMat * vec4(aPos.xyz,1.0f)).xyz;        //将模型空间顶点转世界空间

	Normal = mat3(modelMat) * aNormal;      //将法线转至世界空间

	Normal = transpose(inverse(mat3(modelMat))) * aNormal;

	TexCord = aTexCoord;
}	 