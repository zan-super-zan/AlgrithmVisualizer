#pragma once
#include "GLFW/glfw3.h"
#include <string>

class ImGuiManager
{
public:
	ImGuiManager(GLFWwindow* window);
	~ImGuiManager();

	void NewFrame()const;
	void Render();
	void ShowWidget(const std::string& title, uint32_t nrBars);
private:
	GLFWwindow* m_Window;
};

