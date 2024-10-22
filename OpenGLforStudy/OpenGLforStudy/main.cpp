#include<glad/glad.h>

#include<GLFW/glfw3.h>
//🖤🖤🖤一定要将#include<glad\glad.h>放到#include <GLFW\glfw3.h>前面，
//否则回出现错误：
//#error 指令 : OpenGL header already included, remove this include, glad already provides it OpenGLMFCTest
#include<iostream>
#include "wrapper/fun1.h"
#include "wrapper/errorCheck.h"
#include<assert.h>
#include"application/application.h"

//#include<GL/glew.h>
//好像GL库 与 GLFW库不兼容？
using namespace std;


//声明窗口变化事件回调函数
void frameBufferSizeCallBack(GLFWwindow* window, int width, int height) {
	cout << "new-size:" << width << " , " << height << endl;
	//更新视口大小
	glViewport(0, 0, width, height);
}

//声明键盘消息事件回调函数
void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mod)
{//action:抬起为0
	//mode:表示是否按下control
	
	if (key == GLFW_KEY_W)
	{
		cout << "按键：" << "  " << "w" << endl;
	}

	if (action == GLFW_PRESS)
	{
		cout << "按下了按键" << endl;
	}

	if (action == GLFW_RELEASE)
	{
		cout << "松开了按键" << endl;
	}

	if (mod == GLFW_MOD_CONTROL)
	{
		cout << "contorl模式" << endl;
	}

	if (mod == GLFW_MOD_SHIFT) {
		cout << "shift模式" << endl;
	}


}

//提供给外界的事件响应接口
void OnResize(int width, int height) {
	GL_CALL(glViewport(0, 0, width, height));
	cout << "OnResize" << endl;
}

void OnKey(int key, int scancode, int action, int mod) 
{
	//action:抬起为0
	//mode:表示是否按下control

	if (key == GLFW_KEY_W)
	{
		cout << "按键：" << "  " << "w" << endl;
	}

	if (action == GLFW_PRESS)
	{
		cout << "按下了按键" << endl;
	}

	if (action == GLFW_RELEASE)
	{
		cout << "松开了按键" << endl;
	}

	if (mod == GLFW_MOD_CONTROL)
	{
		cout << "contorl模式" << endl;
	}

	if (mod == GLFW_MOD_SHIFT) {
		cout << "shift模式" << endl;
	}

}


void prepareSingleVBO() {

	//顶点数据
	float positions[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,-0.5f,0.0f
	};//顶点位置：ndc坐标（-1-- +1）
	float colors[]{
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f
	};

	//创建vbo描述信息
	GLuint posVbo = 0;
	GLuint colorVbo = 0;
	GL_CALL(glGenBuffers(1, &posVbo));
	GL_CALL(glGenBuffers(1, &colorVbo));

	//绑定当前vbo到OpenGL当前的vbo插槽，并向当前vbo传输数据
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

	
	
}

void prepareSingleBuffer() {
	//顶点数据
	float positions[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,-0.5f,0.0f
	};//顶点位置：ndc坐标（-1-- +1）
	float colors[]{
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f
	};

	//生成vbo、绑定并传输数据
	GLuint posVbo, colorVbo;
	GL_CALL(glGenBuffers(1,&posVbo));
	GL_CALL(glGenBuffers(1, &colorVbo));

	//绑定后才可向其中传入数据
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

	GLuint vao = 0;
	GL_CALL(glGenVertexArrays(1,&vao));
	GL_CALL(glBindVertexArray(vao));
	//绑定了vbo，下面的属性描述才会与此vbo有关
	//描述位置属性
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(float),(void*)0));
	//描述颜色属性
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));

	GL_CALL(glBindVertexArray(0));

}

void prepareInterleavedVBO() {
	//每一行：每个点的坐标+颜色
	float vertices[] = {
	-0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
	0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
	0.0f,-0.5f,0.0f,0.0f,0.0f,1.0f
	};//顶点位置：ndc坐标（-1-- +1）

	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1,&vbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW));



}


int main()
{

	app->sayHello();

	//设置监听，监听窗体大小变化的消息
	//glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);
	//监听键盘消息
	//glfwSetKeyCallback(window, keyCallBack);

	//窗口初始化
	if (!app->init(800, 600)) {
		return -1;
	}

	app->setResizeCallback(OnResize);
	app->setKeyCallback(OnKey);

	//设置视口大小
	GL_CALL(glViewport(0, 0, 800, 600));
	//设置清理颜色.0
	GL_CALL(glClearColor(0.2f, 0.4f, 0.4f, 0.9f));

	//prepareVBO();

	//设置窗体循环（逐帧）
	while (app->update()) {
		//清理画布
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

	}

	app->destroy();

	return 0;
}
