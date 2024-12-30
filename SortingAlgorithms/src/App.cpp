#include "App.h"
#include "Random.h"
#include "SortAlgorithm.h"

#include <thread>
#include <mutex>


App::App()
	:m_Shader(nullptr), m_Renderer(10000), m_ImGuiManager(nullptr)
{
	m_Window = std::make_unique<Window>(1280, 720, "Alorithm Visualizer");
	m_ImGuiManager = std::make_unique<ImGuiManager>(m_Window->GetNativeWindow());
	m_Camera = std::make_unique<OrthographicCamera>(0.0f,
		static_cast<float>(m_Window->GetWidth()), 0.0f, static_cast<float>(m_Window->GetHeight()));
	m_Shader = std::make_unique<Shader>("shaders/basic.vert", "shaders/basic.frag");
	m_SortContext = std::make_unique<SortContext>();
}

App::~App()
{
	m_Renderer.Shutdown();
}

void App::Run()
{
	Init();

	ShuffleBars();

	std::thread sorterThread([&]() {
		m_SortContext->Sort(m_Rectangles);
		});
	sorterThread.detach();

	while (!m_Window->ShouldClose())
	{
		Update();
		Render();
	}
}

void App::MakeRectangles()
{
	for (uint32_t i = 0; i < m_Rectangles.size(); i++)
		m_Renderer.SubmitRect(m_Rectangles[i], { 1, 1, 1 });

	//for (uint32_t i = 0; i < m_RectangleHeights.size(); i++)
	//	m_Renderer.SubmitRect({ i * m_RectWidth, 0, m_RectWidth, m_RectangleHeights[i] }, { 1, 1, 1 });
}

void App::ShuffleBars()
{
	m_Rectangles.clear();
	m_RectWidth = 5;
	int32_t counter = 0;
	while (m_RectWidth * counter <= m_Window->GetWidth())
	{
		m_Rectangles.emplace_back(FRectangle(counter * m_RectWidth, 0, m_RectWidth, Random::FloatRange(50, 700)));
		++counter;
	}
}

void App::Init()
{
	m_Renderer.Init();
	Random::Init();

	m_Shader->Use();
	m_Shader->SetMat4("ViewProjection", m_Camera->GetViewProjectionMatrix());
	m_Shader->SetMat4("Model", glm::mat4(1.0f));

	// Order matters
	m_Sorts.push_back(std::make_unique<BubbleSort>());
	m_Sorts.push_back(std::make_unique<QuickSort>());
	m_Sorts.push_back(std::make_unique<MergeSort>());

}

void App::Render()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_Window->PollEvents();

	m_Renderer.BeginBatch();

	MakeRectangles();

	m_Renderer.EndBatch();
	m_Renderer.Flush();

	m_ImGuiManager->Render();

	m_Window->SwapBuffers();
}

void App::Update()
{
	m_SortContext->SetSorter(Sort::Sorters::Merge);

	m_ImGuiManager->NewFrame();
	m_ImGuiManager->ShowWidget("Info", m_Rectangles.size());
}

