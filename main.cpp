
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
//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
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

//平行光
LightDirectional lightDirectional(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(glm::radians(45.0f), 0, 0));  //平行光位置无所谓

//点光源
LightPoint lightPoint0(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(glm::radians(45.0f), 0, 0),  glm::vec3(0.0f,1.0f,0.0f));   //点光源方向无所谓
LightPoint lightPoint1(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(0.0f, 0.0f, 1.0f));
LightPoint lightPoint2(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(1.0f, 0.0f, 0.0f));
LightPoint lightPoint3(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));

//聚光灯
LightSpot lightSpot(glm::vec3(0.0f, 3.0f, -1.0f), glm::vec3(glm::radians(90.0f), 0, 0));

float mixS = 0.0f;
float lastX;
float lastY;
bool isFirstMove = true;
float fov = 45.0f;

//鼠标输入
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)    //如果按下ESC键位
	{ 
		glfwSetWindowShouldClose(window, true);  //设置窗口关闭状态为true
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

//鼠标回调函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float deltaX, deltaY;

	if (isFirstMove)
	{
		lastX = xpos;
		lastY = ypos;
		isFirstMove = false;
	}

	deltaX = xpos - lastX;   //检测横向的输入差值
	deltaY = ypos - lastY;  //检测纵向的输入差值

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMove(deltaX, deltaY);
}

//滚轮回调函数
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
	glGenTextures(1, &TexBuffer);   //创建 TexTureBuffer
	glActiveTexture(GL_TEXTURE0+ channel);      //启用GL_TEXTURE_2D通道中的0号
	glBindTexture(GL_TEXTURE_2D, TexBuffer);    //绑定在GL_TEXTURE_2D这个通道上

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   //U方向是Repect
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   //V方向是Repect

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);     //镜头拉远时候，纹理像素变小，使用线性插值
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	  //镜头拉远时候，纹理像素变大，使用线性插值

	stbi_set_flip_vertically_on_load(true);   //将stbi的读取方式从原来的右上角开始变为左下角开始，因为OpenGL的UV原点在左下角

	int width, height, nrChannel;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannel, 0);    //读取图片数据
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, createMode, width, height, 0, sourceMode, GL_UNSIGNED_BYTE, data);  //生成纹理，在现在GL_TEXTURE_2D这个通道上，选择多级渐远层，生成RGB纹理，宽，高，目标图层的通道
		glGenerateMipmap(GL_TEXTURE_2D);      //生成多级渐远层
	}
	else
	{
		std::cout << "Load Image Failed" << std::endl;
	}

	stbi_image_free(data);   //释放数据
	return TexBuffer;
}

int main()
{
	#pragma region Open a Window
	glfwInit();      //初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      //选择OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	    //选择OpenGL的次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);     //自定义流水线，选择核心模式

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);   //创建窗口，并声明它的地址
	if (window == NULL)
	{
		std::cout << "Creat Window Failed" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);    //绑定当前窗口 

	glewExperimental = true;  //初始化GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW Failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);    //创建视口，定义(0,0)为左下角，宽为800，长为600
	#pragma endregion

	#pragma region Setting RenderMode
	//glEnable(GL_CULL_FACE);    //开启剔除模式
	//glCullFace(GL_BACK);      //正面剔除
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);   //线框模式
	glEnable(GL_DEPTH_TEST);     //开启深度测试
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);      //隐藏光标
	glfwSetCursorPosCallback(window, mouse_callback);     //设定鼠标移动的回调函数
	glfwSetScrollCallback(window, scroll_callback);      //设定滚轮滑动的回调函数
	#pragma endregion

	//Shader shader =  Shader("vertexSource.txt", "FragmentSource.txt");    //第一种实例方式
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





	#pragma region OldShaderProgram  (已经文件读取)
	//unsigned int vertexShader;      //创建   顶点着色器 的ID
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);      //指定   顶点着色器的资源位置
	//glCompileShader(vertexShader);          //编译 顶点着色器

	//unsigned int fragmentShader;        //创建   片元着色器  的ID
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);       //指定  片元着色器的资源地址
	//glCompileShader(fragmentShader);         //编译  片元着色器

	//unsigned int shaderProgram;       //创建   着色器（将顶点着色器与片元着色器连接起来）
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	#pragma endregion

	#pragma region Bind VBO到VAO EBO
	unsigned int VAO;           //设置  顶点数组对象  的ID
	glGenVertexArrays(1, &VAO);       //创建   顶点数组对象，一般根据有多少模型，一般一个模型一个VAO
	glBindVertexArray(VAO);         //绑定    顶点数组对象

	unsigned int VBO;        //设置   顶点缓冲对象   的ID
	glGenBuffers(1, &VBO);     //创建   顶点缓冲对象，一般根据有VAO，一个VAO对应一个VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);       //绑定    顶点缓冲对象，由VBO绑定到VAO的ARRAY_BUFFER中

	unsigned int EBO;       //设置   索引缓冲对象   的ID
	glGenBuffers(1, &EBO);      //创建 EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);  //绑定 将ELEMENT_ARRAY_BUFFER指向这个EBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);      //将CPU中的顶点数据传入GPU中，由VBO进行读取

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);   //ELEMENT_ARRAY_BUFFER，去读取索引的数据

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);         //VAO中ArrayBuffer的指针，顶点着色器的layout
																						 //(void*) 类型转换
	glEnableVertexAttribArray(0);   //开启那个特征栏位


	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));         //VAO中ArrayBuffer的指针，顶点着色器的layout
																						 //(void*) 类型转换
	glEnableVertexAttribArray(5);   //开启那个特征栏位

	glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));         //VAO中ArrayBuffer的指针，顶点着色器的layout
																					 //(void*) 类型转换
	glEnableVertexAttribArray(6);   //开启那个特征栏位

	//glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(7);

	#pragma endregion

	#pragma region CreateTexture
	//贴图
	//unsigned int TexBufferA;       //设置   贴图BufferID
	//TexBufferA = LoadTexture("container.jpg", GL_RGB, GL_RGB, 0);

	//unsigned int TexBufferB;
	//TexBufferB = LoadTexture("awesomeface.png", GL_RGBA, GL_RGBA, 5);
	#pragma endregion


	//模型空间转世界空间的  TRS矩阵
	//glm::mat4 modelMat;
	//modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	//世界空间转屏幕空间的    SRT矩阵  （使用逆矩阵是因为要得到此时这个空间的线性组合，因为已知世界空间的位置以及世界空间表示的线性变换）
	glm::mat4 vieMat;

	//屏幕空间转裁剪空间 
	glm::mat4 projMat;
	//projMat = glm::perspective(glm::radians(fov), 800.0f / 600, 0.1f, 100.0f);


	while(!glfwWindowShouldClose(window))       //开启渲染回圈
	{
		processInput(window);   //处理输入信息

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);       //设置清屏颜色
		glClear(GL_COLOR_BUFFER_BIT);          //清除上一帧的颜色缓冲区，并填充清屏颜色
		glClear(GL_DEPTH_BUFFER_BIT);          //每一次绘制完后，清除上一次的   Z缓冲里的数值

		float timeValue = glfwGetTime(); 

		//glm::mat4 modelMat;
		//modelMat = glm::rotate(modelMat,timeValue, glm::vec3(0.0f, 1.0f, 1.0f));

		glBindVertexArray(VAO);         //拿到模型
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


	//Material  -> Select Texture
		glActiveTexture(GL_TEXTURE0+ Shader::DIFFUSE);
		glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);          //将这个ID的贴图，作用于此模型，方便之后采样
		glActiveTexture(GL_TEXTURE0+ Shader::SPECULAR);
		glBindTexture(GL_TEXTURE_2D, myMaterial->specular);          //将这个ID的贴图，作用于此模型，方便之后采样



		//float timeValue = glfwGetTime(); 
		//glm::mat4 trans;                 //声明一个矩阵
		//trans = glm::translate(trans, glm::vec3(0.5f,-0.5f,0.0f));                //位移矩阵，向右移动（0.5f），向下移动（0.5f）
		//trans = glm::rotate(trans, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));       //旋转矩阵，绕z轴，每秒旋转

		#pragma region Uniform读值
		//float timeValue = glfwGetTime();              //Uniform的值是从CPU直接灌入的，所以利用GLFW的接口，提取这个Time值
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");    //获取在ShaderProgram里面的Uniform值的位置，并将其存入某ID中
		//
		//glUseProgram(shaderProgram);     //用什么着色器
		//glUniform4f(vertexColorLocation, 0.5f, greenValue, 0.0f, 1.0f);      //设置Uniform的值，但是要先开启Shader

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
			//glUniform1i(glGetUniformLocation(shader->ID, "ourTexture"), 0);     //往这个位置塞TEXTURE通道中的Texture0
			//glUniform1i(glGetUniformLocation(shader->ID, "ourFace"), 5);     
			glUniform1f(glGetUniformLocation(shader->ID, "mixStrong"), mixS);
			//Material -> Select UniformParameter
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "vieMat"), 1, GL_FALSE, glm::value_ptr(vieMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			//glUniform3f(glGetUniformLocation(shader->ID, "objColor"), 1.0f, 0.5f, 0.3f);
			glUniform3f(glGetUniformLocation(shader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
			
			//LightDirection    平行光
			//myMaterial->shader->SetUniform3f("lightPos", lightDirectional.position);
			myMaterial->shader->SetUniform3f("lightDirectional.dir", lightDirectional.direction);
			myMaterial->shader->SetUniform3f("lightDirectional.color", lightDirectional.color);
			 
			//LightPoint       点光源
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


			//LightSpot    聚光灯
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


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);   //根据Element画什么，画几个顶点，索引类型是什么，从第几个开始
		//glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));      //传入矩阵到顶点着色器，传入一个，不要倒置，类型是Mat4
		//glDrawArrays(GL_TRIANGLES, 0, 6);       //根据Arrays画什么，从第几个索引开始，画几个顶点


		glfwPollEvents();                //监听输入事件
		glfwSwapBuffers(window);          //启用双缓冲来显示图像，前缓冲显示，后缓冲执行渲染指令
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return 0;
}

