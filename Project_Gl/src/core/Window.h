#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
private:
	GLFWwindow* window;
public:
	int screen_width = 1920;
	int screen_height = 1080;

	Window() : window(nullptr) {};
	operator GLFWwindow*() const {
		return window;
	}

	void init();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
