#include "Window.h"

Window::Window(int width, int height, const std::string& title)
	: m_Width(width), m_Height(height)
{
	if(!initializeGLFW())
	{
		throw std::runtime_error("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		terminateGLFW();
		throw std::runtime_error("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(m_Window);
		terminateGLFW();
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback( m_Window,[](GLFWwindow* /*window*/, int newWidth, int newHeight)
		{
			glViewport(0, 0, newWidth, newHeight);
		}
	);

}

Window::~Window()
{
	if (m_Window)
	{
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}
	terminateGLFW();
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(m_Window);
}

GLFWwindow* Window::GetNativeWindow()
{
	return m_Window;
}

bool Window::initializeGLFW()
{
	if (!s_GlfwInitialized)
	{
		if (!glfwInit())
		{
			std::cerr << "Error: GLFW initialization failed." << std::endl;
			return false;
		}
		s_GlfwInitialized = true;
	}
	return true;
}

void Window::terminateGLFW()
{
	if (s_GlfwInitialized)
	{
		glfwTerminate();
		s_GlfwInitialized = false;
	}
}
