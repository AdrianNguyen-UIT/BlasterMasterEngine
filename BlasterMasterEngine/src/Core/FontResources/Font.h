#pragma once
#include "d3dpch.h"

class FontCharacter
{
private:
	char character;
	RECT rect;

public:
	FontCharacter(const char& str = '*', const RECT& r = {0, 0, 0, 0})
		: character(str), rect(r)
	{}

	void SetCharacter(const char& str) { character = str; }
	void SetCharacterRect(const RECT& r) { rect = r; }
	RECT GetRect() { return rect; }
	char GetCharacter() { return character; }
};

class Font
{
protected:
	std::string name;
	std::string spriteName;
	std::vector<FontCharacter> charList;
	Size size;

public:
	Font(const std::string &n = "", const std::string &sn = "", const float& w = 0.0f, const float& h = 0.0f);

	std::string GetName() { return name; }

	void SetName(const std::string& str) { name = str; }
	void SetSize(const float& w, const float& h) { size.width = w; size.height = h; }
	void SetSize(const Size& s) { size = s; }
	Size GetSize() { return size; }
	RECT GetCharacterRect(const char &character);

	std::string GetSpriteName() { return spriteName; }
	virtual void CreateResources() {}
};