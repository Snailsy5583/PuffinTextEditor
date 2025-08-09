#pragma once

#include <memory>
#include <chrono>

#include "Window.h"
#include "Events/Events.h"
#include "Layer.h"

namespace Engine {

#define BIND_EVENT_FUNC(x, obj) std::bind(&x, obj, std::placeholders::_1)

    class Application {
    public:
        Application(unsigned int width, unsigned int height, const char *title);

        ~Application();

        virtual void Run();

        virtual void Update(float deltaTime);

        virtual void OnEvent(Engine::Event &e);

    protected:
        Engine::Window *m_MainWindow;

        Engine::LayerStack m_LayerStack;

        std::chrono::time_point<std::chrono::steady_clock> m_LastFrame;
        float m_DeltaTime;
    };

}