#include "App.h"
#include "Random.h"
#include "SortAlgorithm.h"


App::App()
	:m_Shader(nullptr), m_Renderer(2000), m_ImGuiManager(nullptr), m_RectWidth(1.0f)
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

	ShuffleBars(m_RectWidth);

	while (!m_Window->ShouldClose())
	{
		Update();
		Render();
	}
	m_StopSort = true;

	if (m_SorterThread && m_SorterThread->joinable())
		m_SorterThread->detach();
}

void App::MakeRectangles()
{
	for (uint32_t i = 0; i < m_Rectangles.size(); i++)
		m_Renderer.SubmitRect(m_Rectangles[i], { 1, 1, 1 });

}

void App::ShuffleBars(uint32_t rectWidth)
{
	m_Rectangles.clear();
	int32_t counter = 0;
	while (m_RectWidth * counter <= m_Window->GetWidth())
	{
		m_Rectangles.emplace_back(FRectangle(counter * rectWidth, 0, m_RectWidth, Random::FloatRange(50, 700)));
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
	static Sorters currentSort = Sorters::Bubble;
	static Sorters newSort = Sorters::Bubble;

	m_ImGuiManager->NewFrame();
	m_ImGuiManager->ShowWidget("Info", m_Rectangles.size(), { "Bubble", "Quick", "Merge" }, newSort);

	if (newSort != currentSort)
	{
		m_StopSort = true;

		if (m_SorterThread && m_SorterThread->joinable())
			m_SorterThread->join();

		
		ShuffleBars(m_RectWidth);
		currentSort = newSort;

		m_StopSort = false;

		m_SorterThread = std::make_unique<std::thread>([&]() {
			m_SortContext->SetSorter(currentSort);
			m_SortContext->Sort(m_Rectangles, m_StopSort);
			});
	}
}



