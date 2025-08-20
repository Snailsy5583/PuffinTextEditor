//
// Created by r6awe on 8/8/2025.
//

#ifndef PUFFINTEXTEDITOR_CURSOR_H
#define PUFFINTEXTEDITOR_CURSOR_H

#include "Engine/Renderer.h"
#include <glm/glm.hpp>

class Cursor
{
public:
	Cursor(glm::ivec2 screenPosOffset, glm::vec2 size, const char *vertPath,
		   const char *fragPath);

	void SetScreenSpacePosition(glm::ivec2 pixPos);

	void Move(glm::ivec2 delta);
	void MoveTo(glm::ivec2 pos);

	inline glm::ivec2 GetPosition() const { return m_Position; }
	glm::vec2 GetScreenSpacePos() const;

	void Render(glm::vec2 scrollOffset);

private:
	glm::ivec2 m_Position {};
	glm::ivec2 m_ScreenPositionOffset;
	glm::vec2 m_Size;
	glm::vec4 m_Color {1, 1, 1, 1};

	// rendering
	Engine::RendererObject m_RendererObj;
	Engine::Shader m_Shader;
};


#endif	  // PUFFINTEXTEDITOR_CURSOR_H
