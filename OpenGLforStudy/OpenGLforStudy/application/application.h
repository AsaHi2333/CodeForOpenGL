#pragma once
#include<iostream>
using namespace std;

#define app Application::getInstance()

class GLFWwindow;//避免h当中引用包含头文件导致重复包含

//声明函数指针类型,指向对应声明形式的一个函数
using ResizeCallback = void(*)(int width, int height);
using KeyCallBack = void(*)(int key, int scancode, int action, int mod);

class Application {
public:

	~Application();
	static Application* getInstance();

	bool init(const int& width = 800, const int& height =600);
	bool update();
	void destroy();

	void sayHello() {
		cout << "hello application" << endl;
	}
	//设置回调函数指针
	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyCallback(KeyCallBack callback) { mKeyCallback = callback; }


	uint32_t getWidth()const { return mWidth; }
	uint32_t getHeight()const { return mHeigth; }


private:

	//窗体大小回调函数
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	//键盘回调函数
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);

	static Application* instance;
	//单实例类构造函数需要设定为私有，防止随意创建对象实例
	Application();
	uint32_t mWidth{ 0 };
	uint32_t mHeigth{ 0 };
	GLFWwindow* mWindow{ nullptr };
	//指向一个回调函数的指针变量
	ResizeCallback mResizeCallback{ nullptr };
	KeyCallBack mKeyCallback{ nullptr };
	
	
};
