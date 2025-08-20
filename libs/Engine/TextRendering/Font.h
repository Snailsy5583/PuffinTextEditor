//
// Created by r6awe on 8/13/2025.
//

#ifndef PUFFINTEXTEDITOR_FONT_H
#define PUFFINTEXTEDITOR_FONT_H

#include "../Renderer.h"
#include <ft2build.h>
#include <map>

#include <glm/glm.hpp>
#include FT_FREETYPE_H

namespace Engine
{
	class Font
	{
	public:
		struct FontCharacter {
			Texture texture;	  // ID handle of the glyph texture
			glm::vec2 size;		  // Size of glyph
			glm::vec2 bearing;	  // Offset from baseline to left/top of glyph
			unsigned int advance;	 // Offset to advance to next glyph
		};

		Font(const char *src, const FT_Library *FT, unsigned int size);
		~Font();

		unsigned int GetFontSize() const { return m_FontSize; }

		FontCharacter &GetChar(char c);

	private:
		FT_Face m_FontFace;
		unsigned int m_FontSize;

		const FT_Library *m_FT;

		std::map<char, FontCharacter> m_CharacterSet;
	};
}	 // namespace Engine


#endif	  // PUFFINTEXTEDITOR_FONT_H
