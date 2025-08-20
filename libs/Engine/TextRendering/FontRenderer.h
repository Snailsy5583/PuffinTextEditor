//
// Created by r6awe on 8/13/2025.
//

#ifndef PUFFINTEXTEDITOR_FONTRENDERER_H
#define PUFFINTEXTEDITOR_FONTRENDERER_H

#include "../Renderer.h"
#include "../Shader.h"
#include "Font.h"
#include <glm/glm.hpp>

namespace Engine
{

	class FontRenderer
	{
	public:
		FontRenderer(const char *vertShader, const char *fragShader);
		~FontRenderer();

		Font RegisterFont(const char *fontSrc, unsigned int size);

		float RenderCharacter(char c, Font &font, glm::vec4 color,
							  glm::vec2 pos, float scale);

		void RenderText(const std::string &text, Font &font, glm::vec4 color,
						glm::vec2 pos, float scale);

	private:
		Shader m_FontShader;

		FT_Library m_FT;
	};
}	 // namespace Engine


#endif	  // PUFFINTEXTEDITOR_FONTRENDERER_H
