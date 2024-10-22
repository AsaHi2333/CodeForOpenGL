#pragma once
#include<iostream>
using namespace std;

#define app Application::getInstance()

class GLFWwindow;//����h�������ð���ͷ�ļ������ظ�����

//��������ָ������,ָ���Ӧ������ʽ��һ������
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
	//���ûص�����ָ��
	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
	void setKeyCallback(KeyCallBack callback) { mKeyCallback = callback; }


	uint32_t getWidth()const { return mWidth; }
	uint32_t getHeight()const { return mHeigth; }


private:

	//�����С�ص�����
	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
	//���̻ص�����
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mod);

	static Application* instance;
	//��ʵ���๹�캯����Ҫ�趨Ϊ˽�У���ֹ���ⴴ������ʵ��
	Application();
	uint32_t mWidth{ 0 };
	uint32_t mHeigth{ 0 };
	GLFWwindow* mWindow{ nullptr };
	//ָ��һ���ص�������ָ�����
	ResizeCallback mResizeCallback{ nullptr };
	KeyCallBack mKeyCallback{ nullptr };
	
	
};
