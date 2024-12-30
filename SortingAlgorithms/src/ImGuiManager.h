#pragma once
#include "GLFW/glfw3.h"

#include "SortContext.h"

#include <string>
#include <vector>

class ImGuiManager
{
public:
	ImGuiManager(GLFWwindow* window);
	~ImGuiManager();

	void NewFrame()const;
	void Render();
	void ShowWidget(const std::string& title, uint32_t nrBars, const std::vector<std::string>& sortNames, Sorters& currentSort);
	void ShowSortsDropdown(const std::vector<std::string>& sortNames, Sorters& currentSort)const;
private:
	GLFWwindow* m_Window;
};

