//
// Created by r6awe on 8\\8\\2025.
//

#include "Editor.h"
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>

Editor::Editor() :
	Engine::Application(1280, 720, "Text Editor"),
	m_FontRenderer("shaders/text.vert", "shaders/text.frag"),
	m_SourceCodeProFont(
		m_FontRenderer.RegisterFont("fonts/SourceCodePro-Regular.ttf", 20)),
	m_TextBox({20, 700}, {1240, 680}, 20, m_SourceCodeProFont.GetFontSize(),
			  {1, 1, 1, 0.1f}, {1, 1, 1, 1})
{
	m_LayerStack.Push(m_TextBox.GetLayer());

	// initialize shader projection matrix
	for (Engine::Shader *s : Engine::Shader::p_ShaderList) {
		s->SetUniformMat4("projection", glm::ortho<float>(0, 1280, 0, 720));
	}
}

Editor::~Editor() {}

void Editor::Update(float dt)
{
	//    m_FontRenderer.RenderText("penis penis penis penis",
	//    m_SourceCodeProFont, {1, 0, 1, 1}, {100, 100}, 1); std::cout << 1 / dt
	//    << std::endl;

	m_TextBox.Update(dt);
	m_TextBox.Render(m_FontRenderer, m_SourceCodeProFont);
	m_TextBox.SetScale(1);
}

bool Editor::OnWindowResize(Engine::WindowResizedEvent &e)
{
	m_MainWindow->OnEvent_WindowResize(e);
	for (Engine::Shader *s : Engine::Shader::p_ShaderList) {
		s->SetUniformMat4("projection",
						  glm::ortho<float>(0, e.GetWidth(), 0, e.GetHeight()));
	}
	m_TextBox.SetBounds({20, e.GetHeight() - 20},
						{e.GetWidth() - 40, e.GetHeight() - 40});
	return true;
}

void Editor::DispatchWindowEvents(Engine::EventDispatcher &dispatcher)
{
	dispatcher.Dispatch<Engine::WindowClosedEvent>(
		BIND_EVENT_FUNC(Engine::Window::OnEvent_WindowClosed, m_MainWindow));
	dispatcher.Dispatch<Engine::WindowResizedEvent>(
		BIND_EVENT_FUNC(Editor::OnWindowResize, this));
}
