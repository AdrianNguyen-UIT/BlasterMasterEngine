#include "d3dpch.h"
#include "FontResources.h"
#include "Assets/Font/HealthBarFont.h"
#include "Assets/Font/EndingFont.h"

std::vector<std::shared_ptr<Font>> FontResources::fonts;

FontResources::FontResources()
{
}

FontResources::~FontResources()
{
}

HRESULT FontResources::CreateFontResources()
{
	fonts.reserve(2);
	std::shared_ptr<Font> healthBarFont = std::make_shared<HealthBarFont>();
	healthBarFont->CreateResources();
	fonts.emplace_back(healthBarFont);

	std::shared_ptr<Font> endingFont = std::make_shared<EndingFont>();
	endingFont->CreateResources();
	fonts.emplace_back(endingFont);

	return S_OK;
}

Size FontResources::GetSize(const std::string& fontName)
{
	for (auto font : fonts)
	{
		if (font->GetName() == fontName)
		{
			return font->GetSize();
			break;
		}
	}
}

RECT FontResources::GetRect(const std::string& fontName, const char& character)
{

	for (auto font : fonts)
	{
		if (font->GetName() == fontName)
		{
			return font->GetCharacterRect(character);
			break;
		}
	}
}

std::string FontResources::GetSpriteName(const std::string& fontName)
{
	for (auto font : fonts)
	{
		if (font->GetName() == fontName)
		{
			return font->GetSpriteName();
			break;
		}
	}
}
