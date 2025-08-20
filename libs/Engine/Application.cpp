// #include "glad/glad.h"

#include "Application.h"
#include "Events/WindowEvents.h"

#include <fstream>

namespace Engine
{

	Application::Application(unsigned int width, unsigned int height,
							 const char *title)
	{
		m_DeltaTime = 1 / 60.f;
		if (!glfwInit()) std::cout << "GLFW INIT FAILED\n";

		m_MainWindow = new Engine::Window(
			width, height, title, BIND_EVENT_FUNC(Application::OnEvent, this));
		// m_MainWindow = std::make_unique<Engine::Window>(
		//  width, height, title, BIND_EVENT_FUNC(Application::OnEvent, this));
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			std::cout << "Failed to initialize GLAD\n";

		glViewport(0, 0, width, height);
	}

	Application::~Application() { glfwTerminate(); }

	void Application::Run()
	{
		m_LastFrame = std::chrono::steady_clock::now();

		while (!m_MainWindow->GetShouldCloseWindow()) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Update(m_DeltaTime);
			m_MainWindow->Update();

			m_DeltaTime =
				((float) std::chrono::duration_cast<std::chrono::microseconds>(
					 std::chrono::steady_clock::now() - m_LastFrame)
					 .count()) /
				1000000.f;

			m_LastFrame = std::chrono::steady_clock::now();
		}
	}

	void Application::DispatchWindowEvents(EventDispatcher &dispatcher)
	{
		dispatcher.Dispatch<Engine::WindowClosedEvent>(BIND_EVENT_FUNC(
			Engine::Window::OnEvent_WindowClosed, m_MainWindow));
		dispatcher.Dispatch<Engine::WindowResizedEvent>(BIND_EVENT_FUNC(
			Engine::Window::OnEvent_WindowResize, m_MainWindow));
	}

	void Application::OnEvent(Engine::Event &e)
	{
		Engine::EventDispatcher dispatcher(e);

		DispatchWindowEvents(dispatcher);

		m_LayerStack.OnEvent(e);
	}

	void Application::Update(float deltaTime) {}
}	 // namespace Engine