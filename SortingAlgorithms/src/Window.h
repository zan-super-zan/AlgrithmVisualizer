#pragma once
#include <string>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();
	void PollEvents();
	void SwapBuffers();
	bool ShouldClose();


	GLFWwindow* GetNativeWindow();

	uint32_t GetWidth()const { return m_Width; }
	uint32_t GetHeight()const { return m_Height; }
private:
	static bool initializeGLFW();
	static void terminateGLFW();

private:
	inline static bool s_GlfwInitialized = false;
	GLFWwindow* m_Window;
	uint32_t m_Width, m_Height;
};

