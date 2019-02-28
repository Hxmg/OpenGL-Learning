#include <iostream>
using namespace std;

#include "glad/glad.h"
#include "GLFW/glfw3.h"

int g_WWidth = 1024,g_WHeight = 768;

//一个在屏幕中间的三角形
float vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f
};

//顶点着色器
const char* g_Vertex_Shader_Source = ""
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\n"
"";

//片段着色器 Fragment Shader
const char* g_Fragment_Shader_Source = ""
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\n";

//窗口尺寸改变
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
	glViewport(0,0,g_WWidth = width,g_WHeight = height);
	//cout << "Size Change !\n" ;
}
//初始化着色器
void initShader(){
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //创建一个Vertex Shader对象

	glShaderSource(vertexShader,1,&g_Vertex_Shader_Source,NULL); //将顶点着色器的源码附加到该顶点着色器对象
	glCompileShader(vertexShader);//编译着色器

	int success = 0;
	char infoLog[512];
	glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success); //判断顶点着色器是否编译成功！
	if(!success){
		glGetShaderInfoLog(vertexShader,512,NULL,infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED!!\n" << infoLog << endl; //输出错误信息
	}


	unsigned int fragmentShader; 
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //创建一个Fragment Shader 对象
	glShaderSource(fragmentShader,1,&g_Fragment_Shader_Source,NULL); //将片段着色器的源码附加到片段着色器对象
	glCompileShader(fragmentShader);//编译片段着色器

	glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);//检查片段着色器是否编译成功
	if(!success){
		glGetShaderInfoLog(fragmentShader,512,NULL,infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED!!\n" << infoLog << endl;
	}


	//创建着色器对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader); //将两个编译好的着色器附加到程序对象上
	glLinkProgram(shaderProgram); //链接编译好的着色器

	glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success); //检查着色器是否链接成功！
	if(!success){
		glGetProgramInfoLog(shaderProgram,512,NULL,infoLog); //输出错误信息
		cout << "ERROR::PROGRAM::LINK_FAILED!!\n" << infoLog << endl;
	}else{
		glUseProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

}
int main(){
	cout << "Hello World!" << endl;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);//设置使用的opengl版本
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


	//初始化glfw窗口
	GLFWwindow* window = glfwCreateWindow(g_WWidth,g_WHeight,"LearnOpenGL",NULL,NULL);
	if(window == NULL){
		cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	//通知GLFW将我们窗口的上下文设置为当前线程的主上下文了。
	glfwMakeContextCurrent(window);


	//初始化GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Failed to initalize GLAD!";
		glfwTerminate();
		return -1;
	}

	//设置视口大小
	glViewport(0,0,g_WWidth,g_WHeight);

	//注册窗口大小改变回调
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);


	initShader();

	unsigned int VBO,VAO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);


	while(!glfwWindowShouldClose(window)){

		glClearColor(1.0f,1.0f,1.0f,1.0f);//设置清除的颜色
		glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲区

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}


