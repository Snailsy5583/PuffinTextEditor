//
// Created by r6awe on 8/14/2025.
//

#ifndef PUFFINTEXTEDITOR_TEXTBOX_H
#define PUFFINTEXTEDITOR_TEXTBOX_H

#include "Cursor.h"
#include "Engine/Events/KeyboardEvents.h"
#include "Engine/Events/MouseEvents.h"
#include "Engine/Layer.h"
#include "Engine/TextRendering/FontRenderer.h"
#include <glm/glm.hpp>
#include <string>

class Textbox;

class TextboxLayer : public Engine::Layer
{
public:
	TextboxLayer(Textbox *tb);

	void OnAttach() override {}
	void OnDetach() override {}
	bool OnEvent(Engine::Event &e) override;

private:
	Textbox *m_Textbox;
};

class Textbox
{
public:
	Textbox(glm::vec2 pos, glm::vec2 size, int padding, int fontsize,
			glm::vec4 bgColor, glm::vec4 fgColor);

	std::list<std::string> GetVisibleText();

	void Render(Engine::FontRenderer &fr, Engine::Font &font);

	void Update(float dt);

	inline void SetBounds(glm::vec2 pos, glm::vec2 size)
	{
		m_Bounds[0] = pos;
		m_Bounds[1] = {pos.x + size.x, pos.y - size.y};
	}

	inline void SetBgColor(glm::vec4 bgc) { m_BgColor = bgc; }
	inline void SetFgColor(glm::vec4 fgc) { m_FgColor = fgc; }

	inline void SetScale(float scale) { m_Scale = scale; }

	inline TextboxLayer *GetLayer() { return &m_Layer; }

private:
	inline auto GetCurrentLineIterator()
	{
		return std::next(m_Lines.begin(), m_MainCursor.GetPosition().y);
	}

public:
	bool OnEvent_MouseDown(const Engine::MouseButtonPressedEvent &e);
	bool OnEvent_CharTyped(const Engine::KeyboardCharTypedEvent &e);
	bool OnEvent_SpecialCharTyped(const Engine::KeyboardEvent &e);

	bool OnEvent_KeyboardPressed(const Engine::KeyboardKeyPressedEvent &e);
	bool OnEvent_KeyboardRepeat(const Engine::KeyboardKeyRepeatedEvent &e);
	bool OnEvent_MouseScrolled(const Engine::MouseScrolledEvent &e);

private:
	glm::vec2 m_Bounds[2] = {{}, {}};
	int m_PaddingSize;
	glm::vec2 m_ScrollPosition {};
	glm::vec4 m_BgColor, m_FgColor;
	int m_LineHeight;
	float m_Scale = 1;

	std::list<std::string> m_Lines {""};

	TextboxLayer m_Layer;

	Cursor m_MainCursor;

	// Rendering
	Engine::RendererObject m_Background;
	Engine::Shader m_BackgroundShader;
};


#endif	  // PUFFINTEXTEDITOR_TEXTBOX_H
