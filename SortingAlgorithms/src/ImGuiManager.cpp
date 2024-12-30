#include "ImGuiManager.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_glfw.h"

#include <iostream>
#include <chrono>

ImGuiManager::ImGuiManager(GLFWwindow* window)
	: m_Window(window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 


	if (!window)
	{
		std::cerr << "GLFW window is null!" << std::endl;
		return;
	}
	if (!ImGui::GetCurrentContext())
	{
		std::cerr << "ImGui context is null!" << std::endl;
		return;
	}


	ImGui::StyleColorsDark();

	if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
	{
		std::cerr << "Failed to initialize ImGui GLFW implementation." << std::endl;
		return;
	}
	if (!ImGui_ImplOpenGL3_Init("#version 330")) 
	{
		std::cerr << "Failed to initialize ImGui OpenGL3 implementation." << std::endl;
		return;
	}
}

ImGuiManager::~ImGuiManager()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::NewFrame() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::ShowWidget(const std::string& title, uint32_t nrBars)
{
	ImGui::Begin(title.c_str());

	ImGuiIO& io = ImGui::GetIO();

	ImGui::Text("Frame Rate: %.1f FPS", io.Framerate);
	ImGui::Text("Number of Bars: %u ", nrBars);


	ImGui::End();
}


