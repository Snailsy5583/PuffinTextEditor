//
// Created by r6awe on 8/13/2025.
//

#include "Font.h"
#include <glad/glad.h>
#include <iostream>

using namespace Engine;

Font::Font(const char *src, const FT_Library *FT, unsigned int size) :
	m_FT(FT), m_FontSize(size), m_CharacterSet(), m_FontFace(nullptr)
{
	if (FT_New_Face(*m_FT, src, 0, &m_FontFace)) {
		std::cout << "Error initializing font face: " << src << std::endl;
	}
	FT_Set_Pixel_Sizes(m_FontFace, 0, m_FontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT,
				  1);	 // disable byte-alignment restriction

	for (unsigned char c = 0; c <= CHAR_MAX; c++) {
		// load character glyph
		if (FT_Load_Char(m_FontFace, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		Texture texture((int) m_FontFace->glyph->bitmap.width,
						(int) m_FontFace->glyph->bitmap.rows, 1,
						m_FontFace->glyph->bitmap.buffer);
		texture.Bind();
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		texture.UnBind();

		// now store character for later use
		FontCharacter character {texture,
								 {(float) m_FontFace->glyph->bitmap.width,
								  (float) m_FontFace->glyph->bitmap.rows},
								 {(float) m_FontFace->glyph->bitmap_left,
								  (float) m_FontFace->glyph->bitmap_top},
								 (unsigned int) m_FontFace->glyph->advance.x};
		m_CharacterSet.insert(std::pair<char, FontCharacter>(c, character));
	}

	FT_Done_Face(m_FontFace);
}

Engine::Font::~Font() {}

Font::FontCharacter &Font::GetChar(const char c)
{
	return m_CharacterSet.at(c);
}