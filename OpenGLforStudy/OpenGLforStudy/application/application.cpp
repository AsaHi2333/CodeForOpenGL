#include"application.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>

using namespace std;
Application::Application(){

}
Application::~Application() {

}
//全局变量初始化一次
Application* Application::instance = nullptr;

bool Application::init(const int& width, const int& height) {

	mWidth = width;
	mHeigth = height;

	//初始化GLFW基本环境
	glfwInit();
	//设置OPENGL主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//设置OpenGL次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//设置opengl启用核心模式（非立即渲染模式）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//窗体对象
	mWindow = glfwCreateWindow(mWidth, mHeigth, "LearnOpenGL", NULL, NULL);

	if (mWindow == nullptr)
	{
		return false;
	}
	//设置当前窗体为OpenGL绘制的舞台
	glfwMakeContextCurrent(mWindow);

	// 初始化 GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	//设置窗口尺寸监听
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	//设置键盘监听
	glfwSetKeyCallback(mWindow, keyCallback);

	//*将当前唯一实例存入到mWindow窗体当中
	glfwSetWindowUserPointer(mWindow, this);

	return true;
}

bool Application::update() {

	//查看窗口是否需要关闭
	if (glfwWindowShouldClose(mWindow))
	{
		return false;
	}

	//检查消息队列查看是否有待处理消息（鼠标、键盘、渲染等），若有则批量处理消息并清空队列
	glfwPollEvents();

	//渲染操作

	//切换双缓存
	glfwSwapBuffers(mWindow);

	return true;

}

void Application::destroy() {

	glfwTerminate();
	return ;
}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {

	cout << "Resized" << endl;

	////写法一：自己访问自己
	//if (app->mResizeCallback != nullptr)
	//{
	//	//是以width和height为参数执行了一次mResizeCallback指向的函数
	//	app->mResizeCallback(width, height);
	//}

	//写法二，将单例类的实例存储到窗体中，并以窗体为参数读取出实例，再进行操作
	Application* self = (Application*) glfwGetWindowUserPointer(window);
	if (self->mResizeCallback != nullptr)
	{
		//是以width和height为参数执行了一次mResizeCallback指向的函数
		self->mResizeCallback(width, height);
	}

}

void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mod) {

	cout << "KeyBoard event happened. " << endl;
	Application* self = (Application*)glfwGetWindowUserPointer(window);
	if (self->mKeyCallback != nullptr)
	{
		self->mKeyCallback(key, scancode, action, mod);
	}

}




//get实例的函数中检查实例空值
Application* Application::getInstance() {

	if (instance == nullptr) {
		instance = new Application();
	}
	return instance;

}

