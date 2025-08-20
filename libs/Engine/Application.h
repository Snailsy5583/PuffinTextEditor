#pragma once

#include <chrono>
#include <memory>

#include "Events/Events.h"
#include "Layer.h"
#include "Window.h"

namespace Engine
{

#define BIND_EVENT_FUNC(x, obj) std::bind(&x, obj, std::placeholders::_1)

	class Application
	{
	public:
		Application(unsigned int width, unsigned int height, const char *title);

		~Application();

		virtual void Run();

		virtual void Update(float deltaTime);

		virtual void OnEvent(Engine::Event &e);

		virtual void DispatchWindowEvents(Engine::EventDispatcher &dispatcher);

	protected:
		Engine::Window *m_MainWindow;

		Engine::LayerStack m_LayerStack;

		std::chrono::time_point<std::chrono::steady_clock> m_LastFrame;
		float m_DeltaTime;
	};

}	 // namespace Engine