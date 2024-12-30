#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Window.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "BatchRenderer.h"
#include "SortContext.h"
#include "ImGuiManager.h"
#include "Rectangle.h"

#include <memory>
#include <vector>

class App
{
public:
	App();
	~App();

	void Run();
private:
	void MakeRectangles();
	void ShuffleBars();
	void Init();
	void Render();
	void Update();
private:

	std::unique_ptr<BufferLayout> m_BufferLayout;
	std::unique_ptr<Window> m_Window;
	std::unique_ptr<OrthographicCamera> m_Camera;
	std::unique_ptr<Shader> m_Shader;
	BatchRenderer m_Renderer;	

	float m_RectWidth = 0;
	std::vector<float> m_RectangleHeights;
	std::vector<FRectangle> m_Rectangles;

	
	std::unique_ptr<SortContext> m_SortContext;
	std::vector<std::unique_ptr<Sorter>> m_Sorts;

	std::unique_ptr<ImGuiManager> m_ImGuiManager;
};

