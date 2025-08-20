//
// Created by r6awe on 8/14/2025.
//

#include "Textbox.h"
#include "Engine/Application.h"
#include "Engine/TextRendering/FontRenderer.h"

Textbox::Textbox(glm::vec2 pos, glm::vec2 size, int padding, int fontsize,
				 glm::vec4 bgColor, glm::vec4 fgColor) :
	m_PaddingSize(padding),
	m_BgColor(bgColor), m_FgColor(fgColor), m_Layer(this),
	m_LineHeight(fontsize),
	m_MainCursor({pos.x + padding + 3, pos.y - padding - 5}, {12, 20},
				 "shaders/quad.vert", "shaders/quad.frag"),
	m_BackgroundShader(
		Engine::Shader::Compile("shaders/quad.vert", "shaders/quad.frag")),
	m_Background(Engine::Renderer::GenQuad(
		{pos.x + size.x / 2, pos.y - size.y / 2, 0}, size, &m_BackgroundShader))
{
	SetBounds(pos, size);
	m_BackgroundShader.SetUniformVec("_color", m_BgColor);
}

std::list<std::string> Textbox::GetVisibleText() { return m_Lines; }

void Textbox::Render(Engine::FontRenderer &fr, Engine::Font &font)
{
	Engine::Renderer::SubmitObject(m_Background);

	auto lines = GetVisibleText();
	auto line = lines.begin();
	for (int i = 0; i < lines.size(); i++, line++) {
		auto pos = m_Bounds[0];
		// add padding
		pos += glm::vec2(m_PaddingSize, -(m_PaddingSize + m_LineHeight / 2));
		// add line num
		pos.y -= m_LineHeight * (float) i;
		// add scroll pos
		pos -=
			glm::vec2(m_ScrollPosition.x, -m_ScrollPosition.y * m_LineHeight);
		fr.RenderText(*line, font, m_FgColor, pos, m_Scale);
	}
	m_MainCursor.Render(m_ScrollPosition);
}

void Textbox::Update(float dt) {}

// Event Handlers
bool Textbox::OnEvent_MouseDown(const Engine::MouseButtonPressedEvent &e)
{
	return true;
}

bool Textbox::OnEvent_CharTyped(const Engine::KeyboardCharTypedEvent &e)
{
	if (e.GetChar() == '\n') {
		m_Lines.emplace(std::next(GetCurrentLineIterator()), "");
		m_MainCursor.MoveTo({0, m_MainCursor.GetPosition().y + 1});
		return true;
	}

	*GetCurrentLineIterator() += e.GetChar();
	m_MainCursor.Move({1, 0});
	return true;
}

bool Textbox::OnEvent_SpecialCharTyped(const Engine::KeyboardEvent &e)
{
	glm::ivec2 cursorDelta {0, 0};
	auto curLineIter = GetCurrentLineIterator();
	auto &curLine = *curLineIter;
	switch (e.GetKey()) {
	case GLFW_KEY_TAB:
		curLine += "    ";
		cursorDelta.x += 4;
		break;
	case GLFW_KEY_BACKSPACE: {
		if (curLine.empty()) {
			if (m_Lines.size() != 1) {
				curLineIter = --m_Lines.erase(curLineIter);
				auto newLine = *curLineIter;
				m_MainCursor.MoveTo(
					{newLine.size(), m_MainCursor.GetPosition().y - 1});
			}
			//			break;
			return true;
		}
		curLine.pop_back();
		cursorDelta.x -= 1;
		break;
	}
	case GLFW_KEY_ENTER:
		m_Lines.emplace(std::next(curLineIter), "");
		m_MainCursor.MoveTo({0, m_MainCursor.GetPosition().y + 1});
		return true;

	// cursor movement
	case GLFW_KEY_LEFT:
		cursorDelta.x--;
		break;
	case GLFW_KEY_RIGHT:
		cursorDelta.x++;
		break;
	case GLFW_KEY_UP:
		cursorDelta.y--;
		break;
	case GLFW_KEY_DOWN:
		cursorDelta.y++;
		break;

	case GLFW_KEY_V:
		if (e.GetModifiers() == GLFW_MOD_CONTROL) {
			for (char c : e.GetWindow().GetClipboard())
				OnEvent_CharTyped(
					Engine::KeyboardCharTypedEvent(e.GetWindow(), c));
		}
		break;

	default:
		return false;
	}

	m_MainCursor.Move(cursorDelta);
}

bool Textbox::OnEvent_KeyboardRepeat(const Engine::KeyboardKeyRepeatedEvent &e)
{
	return OnEvent_SpecialCharTyped(e);
}

bool Textbox::OnEvent_KeyboardPressed(const Engine::KeyboardKeyPressedEvent &e)
{
	return OnEvent_SpecialCharTyped(e);
}

bool Textbox::OnEvent_MouseScrolled(const Engine::MouseScrolledEvent &e)
{
	auto visibleLinesNum =
		(abs(m_Bounds[1].y - m_Bounds[0].y) - m_PaddingSize * 2.f) /
		m_LineHeight;
	if (m_Lines.size() > visibleLinesNum)
		m_ScrollPosition -= e.GetScrollAmount();
	return true;
}

//////////////////////////////// TextboxLayer //////////////////////////////////

TextboxLayer::TextboxLayer(Textbox *tb) : m_Textbox(tb) {}

bool TextboxLayer::OnEvent(Engine::Event &e)
{
	Engine::EventDispatcher dispatcher(e);

	if (dispatcher.Dispatch<Engine::MouseButtonPressedEvent>(
			BIND_EVENT_FUNC(Textbox::OnEvent_MouseDown, m_Textbox)))
		return true;
	if (dispatcher.Dispatch<Engine::MouseScrolledEvent>(
			BIND_EVENT_FUNC(Textbox::OnEvent_MouseScrolled, m_Textbox))) {
		return true;
	}
	if (dispatcher.Dispatch<Engine::KeyboardCharTypedEvent>(
			BIND_EVENT_FUNC(Textbox::OnEvent_CharTyped, m_Textbox)))
		return true;
	if (dispatcher.Dispatch<Engine::KeyboardKeyRepeatedEvent>(
			BIND_EVENT_FUNC(Textbox::OnEvent_KeyboardRepeat, m_Textbox)))
		return true;
	if (dispatcher.Dispatch<Engine::KeyboardKeyPressedEvent>(
			BIND_EVENT_FUNC(Textbox::OnEvent_KeyboardPressed, m_Textbox)))
		return true;

	return false;
}