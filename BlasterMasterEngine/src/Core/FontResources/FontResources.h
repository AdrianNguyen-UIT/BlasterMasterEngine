#pragma once
#include "Font.h"

class FontResources
{
private:
	static std::vector<std::shared_ptr<Font>> fonts;

public:
	FontResources();
	~FontResources();

	HRESULT CreateFontResources();

	static Size GetSize(const std::string &fontName);
	static RECT GetRect(const std::string &fontName, const char &character);
	static std::string GetSpriteName(const std::string& fontName);
};