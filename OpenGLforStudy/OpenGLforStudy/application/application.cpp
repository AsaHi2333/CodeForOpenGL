#include"application.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>

using namespace std;
Application::Application(){

}
Application::~Application() {

}
//ȫ�ֱ�����ʼ��һ��
Application* Application::instance = nullptr;

bool Application::init(const int& width, const int& height) {

	mWidth = width;
	mHeigth = height;

	//��ʼ��GLFW��������
	glfwInit();
	//����OPENGL���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//����OpenGL�ΰ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//����opengl���ú���ģʽ����������Ⱦģʽ��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//�������
	mWindow = glfwCreateWindow(mWidth, mHeigth, "LearnOpenGL", NULL, NULL);

	if (mWindow == nullptr)
	{
		return false;
	}
	//���õ�ǰ����ΪOpenGL���Ƶ���̨
	glfwMakeContextCurrent(mWindow);

	// ��ʼ�� GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	//���ô��ڳߴ����
	glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);
	//���ü��̼���
	glfwSetKeyCallback(mWindow, keyCallback);

	//*����ǰΨһʵ�����뵽mWindow���嵱��
	glfwSetWindowUserPointer(mWindow, this);

	return true;
}

bool Application::update() {

	//�鿴�����Ƿ���Ҫ�ر�
	if (glfwWindowShouldClose(mWindow))
	{
		return false;
	}

	//�����Ϣ���в鿴�Ƿ��д�������Ϣ����ꡢ���̡���Ⱦ�ȣ�������������������Ϣ����ն���
	glfwPollEvents();

	//��Ⱦ����

	//�л�˫����
	glfwSwapBuffers(mWindow);

	return true;

}

void Application::destroy() {

	glfwTerminate();
	return ;
}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {

	cout << "Resized" << endl;

	////д��һ���Լ������Լ�
	//if (app->mResizeCallback != nullptr)
	//{
	//	//����width��heightΪ����ִ����һ��mResizeCallbackָ��ĺ���
	//	app->mResizeCallback(width, height);
	//}

	//д���������������ʵ���洢�������У����Դ���Ϊ������ȡ��ʵ�����ٽ��в���
	Application* self = (Application*) glfwGetWindowUserPointer(window);
	if (self->mResizeCallback != nullptr)
	{
		//����width��heightΪ����ִ����һ��mResizeCallbackָ��ĺ���
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




//getʵ���ĺ����м��ʵ����ֵ
Application* Application::getInstance() {

	if (instance == nullptr) {
		instance = new Application();
	}
	return instance;

}

