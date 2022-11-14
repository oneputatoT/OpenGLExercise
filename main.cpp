
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#pragma region VertexInfo

//float vertices[] = {
//	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
//};

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

unsigned int indices[]
{
	0,3,2,
	2,1,0
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion



Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

//ƽ�й�
LightDirectional lightDirectional(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(glm::radians(45.0f), 0, 0));  //ƽ�й�λ������ν

//���Դ
LightPoint lightPoint0(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(glm::radians(45.0f), 0, 0),  glm::vec3(0.0f,1.0f,0.0f));   //���Դ��������ν
LightPoint lightPoint1(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(0.0f, 0.0f, 1.0f));
LightPoint lightPoint2(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(1.0f, 0.0f, 0.0f));
LightPoint lightPoint3(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));

//�۹��
LightSpot lightSpot(glm::vec3(0.0f, 3.0f, -1.0f), glm::vec3(glm::radians(90.0f), 0, 0));

float mixS = 0.0f;
float lastX;
float lastY;
bool isFirstMove = true;
float fov = 45.0f;

//�������
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)    //�������ESC��λ
	{ 
		glfwSetWindowShouldClose(window, true);  //���ô��ڹر�״̬Ϊtrue
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (mixS < 1.0f)
		{
			mixS += 0.01f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (mixS > 0.0f)
		{
			mixS -= 0.01f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.SpeedZ = 1.0f;
	}
	else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.SpeedZ = -1.0f;
	}
	else
	{
		camera.SpeedZ = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.SpeedD = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.SpeedD = 1.0f;
	}
	else
	{
		camera.SpeedD = 0.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.SpeedY = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.SpeedY = -1.0f;
	}
	else
	{
		camera.SpeedY = 0.0f;
	}
}

//���ص�����
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float deltaX, deltaY;

	if (isFirstMove)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMove = false;
	}

	deltaX = xpos - lastX;   //������������ֵ
	deltaY = ypos - lastY;  //�������������ֵ

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMove(deltaX, deltaY);
}

//���ֻص�����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 60.0f)
		fov = 60.0f;
}

unsigned int LoadTexture(const char* texturePath, GLint createMode, GLenum sourceMode, int channel)
{
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);   //���� TexTureBuffer
	glActiveTexture(GL_TEXTURE0+ channel);      //����GL_TEXTURE_2Dͨ���е�0��
	glBindTexture(GL_TEXTURE_2D, TexBuffer);    //����GL_TEXTURE_2D���ͨ����

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   //U������Repect
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   //V������Repect

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);     //��ͷ��Զʱ���������ر�С��ʹ�����Բ�ֵ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	  //��ͷ��Զʱ���������ر��ʹ�����Բ�ֵ

	stbi_set_flip_vertically_on_load(true);   //��stbi�Ķ�ȡ��ʽ��ԭ�������Ͻǿ�ʼ��Ϊ���½ǿ�ʼ����ΪOpenGL��UVԭ�������½�

	int width, height, nrChannel;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannel, 0);    //��ȡͼƬ����
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, createMode, width, height, 0, sourceMode, GL_UNSIGNED_BYTE, data);  //��������������GL_TEXTURE_2D���ͨ���ϣ�ѡ��༶��Զ�㣬����RGB�������ߣ�Ŀ��ͼ���ͨ��
		glGenerateMipmap(GL_TEXTURE_2D);      //���ɶ༶��Զ��
	}
	else
	{
		std::cout << "Load Image Failed" << std::endl;
	}

	stbi_image_free(data);   //�ͷ�����
	return TexBuffer;
}

int main()
{
	#pragma region Open a Window
	glfwInit();      //��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      //ѡ��OpenGL�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	    //ѡ��OpenGL�Ĵΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);     //�Զ�����ˮ�ߣ�ѡ�����ģʽ

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);   //�������ڣ����������ĵ�ַ
	if (window == NULL)
	{
		std::cout << "Creat Window Failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);    //�󶨵�ǰ���� 

	glewExperimental = true;  //��ʼ��GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW Failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);    //�����ӿڣ�����(0,0)Ϊ���½ǣ���Ϊ800����Ϊ600
	#pragma endregion

	#pragma region Setting RenderMode
	//glEnable(GL_CULL_FACE);    //�����޳�ģʽ
	//glCullFace(GL_BACK);      //�����޳�
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   //�߿�ģʽ
	glEnable(GL_DEPTH_TEST);     //������Ȳ���
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);      //���ع��
	glfwSetCursorPosCallback(window, mouse_callback);     //�趨����ƶ��Ļص�����
	glfwSetScrollCallback(window, scroll_callback);      //�趨���ֻ����Ļص�����
	#pragma endregion

	//Shader shader =  Shader("vertexSource.txt", "FragmentSource.txt");    //��һ��ʵ����ʽ
	//shader.text();
	
	#pragma region Init Shader
	Shader* shader = new Shader("vertexSource.vert", "fragmentSource.frag");
	#pragma endregion

#pragma region Init Material
	Material* myMaterial = new Material(shader,
		glm::vec3(1.0f, 1.0f, 1.0f),         //ambien
		LoadTexture("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),         //diffuse
		LoadTexture("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),         //specular
		32.0f);
#pragma endregion





	#pragma region OldShaderProgram  (�Ѿ��ļ���ȡ)
	//unsigned int vertexShader;      //����   ������ɫ�� ��ID
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);      //ָ��   ������ɫ������Դλ��
	//glCompileShader(vertexShader);          //���� ������ɫ��

	//unsigned int fragmentShader;        //����   ƬԪ��ɫ��  ��ID
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);       //ָ��  ƬԪ��ɫ������Դ��ַ
	//glCompileShader(fragmentShader);         //����  ƬԪ��ɫ��

	//unsigned int shaderProgram;       //����   ��ɫ������������ɫ����ƬԪ��ɫ������������
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	#pragma endregion

	#pragma region Bind VBO��VAO EBO
	unsigned int VAO;           //����  �����������  ��ID
	glGenVertexArrays(1, &VAO);       //����   �����������һ������ж���ģ�ͣ�һ��һ��ģ��һ��VAO
	glBindVertexArray(VAO);         //��    �����������

	unsigned int VBO;        //����   ���㻺�����   ��ID
	glGenBuffers(1, &VBO);     //����   ���㻺�����һ�������VAO��һ��VAO��Ӧһ��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);       //��    ���㻺�������VBO�󶨵�VAO��ARRAY_BUFFER��

	unsigned int EBO;       //����   �����������   ��ID
	glGenBuffers(1, &EBO);      //���� EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  //�� ��ELEMENT_ARRAY_BUFFERָ�����EBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);      //��CPU�еĶ������ݴ���GPU�У���VBO���ж�ȡ

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);   //ELEMENT_ARRAY_BUFFER��ȥ��ȡ����������

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);         //VAO��ArrayBuffer��ָ�룬������ɫ����layout
																						 //(void*) ����ת��
	glEnableVertexAttribArray(0);   //�����Ǹ�������λ


	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));         //VAO��ArrayBuffer��ָ�룬������ɫ����layout
																						 //(void*) ����ת��
	glEnableVertexAttribArray(5);   //�����Ǹ�������λ

	glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));         //VAO��ArrayBuffer��ָ�룬������ɫ����layout
																					 //(void*) ����ת��
	glEnableVertexAttribArray(6);   //�����Ǹ�������λ

	//glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(7);

	#pragma endregion

	#pragma region CreateTexture
	//��ͼ
	//unsigned int TexBufferA;       //����   ��ͼBufferID
	//TexBufferA = LoadTexture("container.jpg", GL_RGB, GL_RGB, 0);

	//unsigned int TexBufferB;
	//TexBufferB = LoadTexture("awesomeface.png", GL_RGBA, GL_RGBA, 5);
	#pragma endregion


	//ģ�Ϳռ�ת����ռ��  TRS����
	//glm::mat4 modelMat;
	//modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	//����ռ�ת��Ļ�ռ��    SRT����  ��ʹ�����������ΪҪ�õ���ʱ����ռ��������ϣ���Ϊ��֪����ռ��λ���Լ�����ռ��ʾ�����Ա任��
	glm::mat4 vieMat;

	//��Ļ�ռ�ת�ü��ռ� 
	glm::mat4 projMat;
	//projMat = glm::perspective(glm::radians(fov), 800.0f / 600, 0.1f, 100.0f);


	while(!glfwWindowShouldClose(window))       //������Ⱦ��Ȧ
	{
		processInput(window);   //����������Ϣ

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);       //����������ɫ
		glClear(GL_COLOR_BUFFER_BIT);          //�����һ֡����ɫ�������������������ɫ
		glClear(GL_DEPTH_BUFFER_BIT);          //ÿһ�λ�����������һ�ε�   Z���������ֵ

		float timeValue = glfwGetTime(); 

		//glm::mat4 modelMat;
		//modelMat = glm::rotate(modelMat,timeValue, glm::vec3(0.0f, 1.0f, 1.0f));

		glBindVertexArray(VAO);         //�õ�ģ��
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	//Material  -> Select Texture
		glActiveTexture(GL_TEXTURE0+ Shader::DIFFUSE);
		glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);          //�����ID����ͼ�������ڴ�ģ�ͣ�����֮�����
		glActiveTexture(GL_TEXTURE0+ Shader::SPECULAR);
		glBindTexture(GL_TEXTURE_2D, myMaterial->specular);          //�����ID����ͼ�������ڴ�ģ�ͣ�����֮�����



		//float timeValue = glfwGetTime(); 
		//glm::mat4 trans;                 //����һ������
		//trans = glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));                //λ�ƾ��������ƶ���0.5f���������ƶ���0.5f��
		//trans = glm::rotate(trans, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));       //��ת������z�ᣬÿ����ת

		#pragma region Uniform��ֵ
		//float timeValue = glfwGetTime();              //Uniform��ֵ�Ǵ�CPUֱ�ӹ���ģ���������GLFW�Ľӿڣ���ȡ���Timeֵ
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");    //��ȡ��ShaderProgram�����Uniformֵ��λ�ã����������ĳID��
		//
		//glUseProgram(shaderProgram);     //��ʲô��ɫ��
		//glUniform4f(vertexColorLocation, 0.5f, greenValue, 0.0f, 1.0f);      //����Uniform��ֵ������Ҫ�ȿ���Shader

		#pragma endregion

		camera.UpdateCameraPos();
		vieMat = camera.GetViewMatrix();
		projMat = glm::perspective(glm::radians(fov), 800.0f / 600, 0.1f, 100.0f);

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 modelMat;
			modelMat = glm::translate(modelMat, cubePositions[i]);
			//modelMat = glm::rotate(modelMat, timeValue*i*0.2f, glm::vec3(0.0f, 1.0f, 1.0f));

			//Material -> Selcet Shader
			shader->Use();
			//glUniform1i(glGetUniformLocation(shader->ID, "ourTexture"), 0);     //�����λ����TEXTUREͨ���е�Texture0
			//glUniform1i(glGetUniformLocation(shader->ID, "ourFace"), 5);     
			glUniform1f(glGetUniformLocation(shader->ID, "mixStrong"), mixS);
			//Material -> Select UniformParameter
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "vieMat"), 1, GL_FALSE, glm::value_ptr(vieMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			//glUniform3f(glGetUniformLocation(shader->ID, "objColor"), 1.0f, 0.5f, 0.3f);
			glUniform3f(glGetUniformLocation(shader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
			
			//LightDirection    ƽ�й�
			//myMaterial->shader->SetUniform3f("lightPos", lightDirectional.position);
			myMaterial->shader->SetUniform3f("lightDirectional.dir", lightDirectional.direction);
			myMaterial->shader->SetUniform3f("lightDirectional.color", lightDirectional.color);
			 
			//LightPoint       ���Դ
		#pragma region P0
			myMaterial->shader->SetUniform3f("lightPoint0.position", lightPoint0.position);
			myMaterial->shader->SetUniform3f("lightPoint0.color", lightPoint0.color);
			myMaterial->shader->SetUniform1f("lightPoint0.constant", lightPoint0.constant);
			myMaterial->shader->SetUniform1f("lightPoint0.linear", lightPoint0.linear);
			myMaterial->shader->SetUniform1f("lightPoint0.quadratic", lightPoint0.quadratic);
		#pragma endregion

		#pragma region P1
			myMaterial->shader->SetUniform3f("lightPoint1.position", lightPoint1.position);
			myMaterial->shader->SetUniform3f("lightPoint1.color", lightPoint1.color);
			myMaterial->shader->SetUniform1f("lightPoint1.constant", lightPoint1.constant);
			myMaterial->shader->SetUniform1f("lightPoint1.linear", lightPoint1.linear);
			myMaterial->shader->SetUniform1f("lightPoint1.quadratic", lightPoint1.quadratic);
		#pragma endregion

		#pragma region P2
			myMaterial->shader->SetUniform3f("lightPoint2.position", lightPoint2.position);
			myMaterial->shader->SetUniform3f("lightPoint2.color", lightPoint2.color);
			myMaterial->shader->SetUniform1f("lightPoint2.constant", lightPoint2.constant);
			myMaterial->shader->SetUniform1f("lightPoint2.linear", lightPoint2.linear);
			myMaterial->shader->SetUniform1f("lightPoint2.quadratic", lightPoint2.quadratic);
		#pragma endregion

		#pragma region P3
			myMaterial->shader->SetUniform3f("lightPoint3.position", lightPoint3.position);
			myMaterial->shader->SetUniform3f("lightPoint3.color", lightPoint3.color);
			myMaterial->shader->SetUniform1f("lightPoint3.constant", lightPoint3.constant);
			myMaterial->shader->SetUniform1f("lightPoint3.linear", lightPoint3.linear);
			myMaterial->shader->SetUniform1f("lightPoint3.quadratic", lightPoint3.quadratic);
		#pragma endregion


			//LightSpot    �۹��
			myMaterial->shader->SetUniform3f("lightSpot.position", lightSpot.position);
			myMaterial->shader->SetUniform3f("lightSpot.dir", lightSpot.direction);
			myMaterial->shader->SetUniform3f("lightSpot.color", lightSpot.color);
			myMaterial->shader->SetUniform1f("lightSpot.cosphyInner", lightSpot.cosphyInner);
			myMaterial->shader->SetUniform1f("lightSpot.cosphyOutter", lightSpot.cosphyOutter);

			glUniform3f(glGetUniformLocation(shader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			//glUniform3f(glGetUniformLocation(shader->ID, "specularColor"), 1.0f, 1.0f, 1.0f);

			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);


			//DrawCall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   //����Element��ʲô�����������㣬����������ʲô���ӵڼ�����ʼ
		//glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));      //������󵽶�����ɫ��������һ������Ҫ���ã�������Mat4
		//glDrawArrays(GL_TRIANGLES, 0, 6);       //����Arrays��ʲô���ӵڼ���������ʼ������������


		glfwPollEvents();                //���������¼�
		glfwSwapBuffers(window);          //����˫��������ʾͼ��ǰ������ʾ���󻺳�ִ����Ⱦָ��
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return 0;
}

