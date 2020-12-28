#include "d3dpch.h"
#include "Font.h"

Font::Font(const std::string& n, const std::string& sn, const float& w, const float& h)
	: name(n), spriteName(sn), size(w, h)
{
}

RECT Font::GetCharacterRect(const char& character)
{
	for (auto c : charList)
	{
		if (c.GetCharacter() == character)
		{
			return c.GetRect();
			break;
		}
	}
}
