#include "d3dpch.h"
#include "HealthBarFont.h"

HealthBarFont::HealthBarFont()
	: Font("Health Bar Font", "Health_Bar_Font_Texture", 30, 30)
{
}

void HealthBarFont::CreateResources()
{
	charList.reserve(36);

	FontCharacter character;
	RECT rect;
	
	rect = { 2, 1, 32, 31 };
	character.SetCharacter('A');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 66, 1 , 96, 31 };
	character.SetCharacter('B');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 130, 1, 160, 31 };
	character.SetCharacter('C');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 194, 1, 224, 31 };
	character.SetCharacter('D');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 258, 1, 288, 31 };
	character.SetCharacter('E');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 322, 1, 352, 31 };
	character.SetCharacter('F');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 34, 33, 64, 63 };
	character.SetCharacter('G');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 98, 33, 128, 63 };
	character.SetCharacter('H');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 162, 33, 192, 63 };
	character.SetCharacter('I');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 226, 33, 256, 63 };
	character.SetCharacter('J');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 290, 33, 320, 63 };
	character.SetCharacter('K');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 354, 33, 384, 63 };
	character.SetCharacter('L');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 2, 65, 32, 95 };
	character.SetCharacter('M');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 66, 65, 96, 95 };
	character.SetCharacter('N');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 130, 65, 160, 95 };
	character.SetCharacter('O');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 194, 65, 224, 95 };
	character.SetCharacter('P');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 258, 65, 288, 95 };
	character.SetCharacter('Q');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 322, 65, 352, 95 };
	character.SetCharacter('R');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 34, 97, 64, 127 };
	character.SetCharacter('S');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 98, 97, 128, 127 };
	character.SetCharacter('T');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 162, 97, 192, 127 };
	character.SetCharacter('U');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 226, 97, 256, 127 };
	character.SetCharacter('V');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 290, 97, 320, 127 };
	character.SetCharacter('W');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 354, 97, 384, 127 };
	character.SetCharacter('X');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 2, 129, 32, 159 };
	character.SetCharacter('Y');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 66, 129, 99, 159 };
	character.SetCharacter('Z');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 194, 129, 224, 159 };
	character.SetCharacter('1');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 258, 129, 288, 159 };
	character.SetCharacter('2');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 322, 129, 352, 159 };
	character.SetCharacter('3');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 34, 161, 64, 191 };
	character.SetCharacter('4');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 98, 161, 128, 191 };
	character.SetCharacter('5');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 162, 161, 192, 191 };
	character.SetCharacter('6');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 226, 161, 256, 191 };
	character.SetCharacter('7');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 290, 161, 320, 191 };
	character.SetCharacter('8');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 354, 161, 384, 191 };
	character.SetCharacter('9');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 2, 193, 32, 223 };
	character.SetCharacter('0');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);

	rect = { 66, 193, 96, 223 };
	character.SetCharacter(' ');
	character.SetCharacterRect(rect);
	charList.emplace_back(character);
}