#include <iostream>
using namespace std;

#include "glad/glad.h"
#include "GLFW/glfw3.h"

int g_WWidth = 1024,g_WHeight = 768;


//窗口尺寸改变
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
	glViewport(0,0,g_WWidth = width,g_WHeight = height);
	//cout << "Size Change !\n" ;
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


	while(!glfwWindowShouldClose(window)){

		glClearColor(1.0f,1.0f,1.0f,1.0f);//设置清除的颜色
		glClear(GL_COLOR_BUFFER_BIT);//清除颜色缓冲区

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}


