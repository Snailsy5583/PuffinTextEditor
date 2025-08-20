//
// Created by r6awe on 8/13/2025.
//

#include "FontRenderer.h"
#include <iostream>

using namespace Engine;

FontRenderer::FontRenderer(const char *vertShader, const char *fragShader) :
	m_FontShader(Shader::Compile(vertShader, fragShader))
{
	if (FT_Init_FreeType(&m_FT)) {
		std::cout << "Error initializing freetype." << std::endl;
	}
}

FontRenderer::~FontRenderer() { FT_Done_FreeType(m_FT); }

Font FontRenderer::RegisterFont(const char *fontSrc, unsigned int size)
{
	return {fontSrc, &m_FT, size};
}

float FontRenderer::RenderCharacter(char c, Font &font, glm::vec4 color,
									glm::vec2 pos, float scale)
{
	// special whitespace characters
	Font::FontCharacter &fontChar = font.GetChar(c);
	switch (c) {
	case '\t':
		return (float) (fontChar.advance >> 6) * 4 * scale;
	default:
		break;
	}

	glm::vec3 charPos = glm::vec3(pos.x, pos.y, 0);
	charPos.x += fontChar.bearing.x * scale;
	charPos.y -= (fontChar.size.y - fontChar.bearing.y) * scale;
	charPos += glm::vec3(fontChar.size, 0) / 2.f;
	auto quad =
		Renderer::GenQuad(charPos, fontChar.size * scale, &m_FontShader);
	fontChar.texture.Bind();
	m_FontShader.SetUniformVec("textColor", color);
	Renderer::SubmitObject(quad);
	fontChar.texture.UnBind();
	Renderer::DeleteQuad(quad);

	return (float) (fontChar.advance >> 6) * scale;
}

void FontRenderer::RenderText(const std::string &text, Font &font,
							  glm::vec4 color, glm::vec2 pos, float scale)
{
	glm::vec2 starting_pos = pos;
	for (char c : text) {
		if (c == '\n') {
			pos.y -= (float) font.GetFontSize();
			pos.x = starting_pos.x;
			continue;
		}
		pos.x += RenderCharacter(c, font, color, pos, scale);
	}
}
