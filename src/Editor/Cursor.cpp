//
// Created by r6awe on 8/8/2025.
//

#include "Cursor.h"

Cursor::Cursor(glm::ivec2 screenPosOffset, glm::vec2 size, const char *vertPath,
			   const char *fragPath) :
	m_ScreenPositionOffset(screenPosOffset),
	m_Shader(Engine::Shader::Compile(vertPath, fragPath)), m_Size(size)
{
	m_RendererObj = Engine::Renderer::GenQuad(glm::vec3(screenPosOffset, 0),
											  m_Size, &m_Shader);
	m_Shader.SetUniformVec("_color", m_Color);
}

void Cursor::Move(glm::ivec2 delta) { MoveTo(m_Position + delta); }

void Cursor::MoveTo(glm::ivec2 pos)
{
	m_Position = pos;
	Engine::Renderer::MoveQuad(m_RendererObj, glm::vec3(GetScreenSpacePos(), 0),
							   m_Size);
}

void Cursor::Render(glm::vec2 scrollOffset)
{
	Engine::Renderer::MoveQuad(
		m_RendererObj,
		glm::vec3(GetScreenSpacePos() + scrollOffset * m_Size, 0), m_Size);
	Engine::Renderer::SubmitObject(m_RendererObj);
}

glm::vec2 Cursor::GetScreenSpacePos() const
{
	return (glm::vec2) m_ScreenPositionOffset +
		   glm::vec2(m_Position.x * m_Size.x, -m_Position.y * m_Size.y);
}

void Cursor::SetScreenSpacePosition(glm::ivec2 pixPos) {}
