//
// Created by r6awe on 8/8/2025.
//

#ifndef PUFFINTEXTEDITOR_EDITOR_H
#define PUFFINTEXTEDITOR_EDITOR_H

#include "Engine/TextRendering/FontRenderer.h"
#include "Textbox.h"
#include <Engine/Application.h>

enum EditorState { Normal = 0, Edit, Select, Command };

class Editor : public Engine::Application
{
public:
	Editor();

	~Editor();

	void Update(float dt) override;

	bool OnWindowResize(Engine::WindowResizedEvent &e);

	void DispatchWindowEvents(Engine::EventDispatcher &dispatcher) override;

private:
	EditorState m_CurState = Normal;
	Engine::FontRenderer m_FontRenderer;
	Engine::Font m_SourceCodeProFont;
	Textbox m_TextBox;
};


#endif	  // PUFFINTEXTEDITOR_EDITOR_H
