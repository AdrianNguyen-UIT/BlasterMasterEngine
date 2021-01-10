#include "d3dpch.h"
#include "EndingFont.h"

EndingFont::EndingFont()
	: Font("Ending Font", "Ending_Font_Texture", 25, 25)
{
}

void EndingFont::CreateResources()
{
	int characterNumb = 40;
	charList.reserve(characterNumb);
	
	FontCharacter character;
	RECT rect;

	size_t width = 25;
	size_t height = 25;
	size_t xOffset = 2;
	size_t yOffset = 2;

	for (size_t index = 0; index < characterNumb; index++)
	{
		rect.left = 2 + (index % 26) * (width + xOffset);
		rect.top = 2 + (index / 26) * (height + yOffset);
		rect.right = rect.left + width + 1;
		rect.bottom = rect.top + height + 1;
		character.SetCharacterRect(rect);
		charList.emplace_back(character);
	}

	charList[0].SetCharacter('A');
	charList[1].SetCharacter('B');
	charList[2].SetCharacter('C');
	charList[3].SetCharacter('D');
	charList[4].SetCharacter('E');
	charList[5].SetCharacter('F');
	charList[6].SetCharacter('G');
	charList[7].SetCharacter('H');
	charList[8].SetCharacter('I');
	charList[9].SetCharacter('J');
	charList[10].SetCharacter('K');
	charList[11].SetCharacter('L');
	charList[12].SetCharacter('M');
	charList[13].SetCharacter('N');
	charList[14].SetCharacter('O');
	charList[15].SetCharacter('P');
	charList[16].SetCharacter('Q');
	charList[17].SetCharacter('R');
	charList[18].SetCharacter('S');
	charList[19].SetCharacter('T');
	charList[20].SetCharacter('U');
	charList[21].SetCharacter('V');
	charList[22].SetCharacter('W');
	charList[23].SetCharacter('X');
	charList[24].SetCharacter('Y');
	charList[25].SetCharacter('Z');
	charList[26].SetCharacter('0');
	charList[27].SetCharacter('1');
	charList[28].SetCharacter('2');
	charList[29].SetCharacter('3');
	charList[30].SetCharacter('4');
	charList[31].SetCharacter('5');
	charList[32].SetCharacter('6');
	charList[33].SetCharacter('7');
	charList[34].SetCharacter('8');
	charList[35].SetCharacter('9');
	charList[36].SetCharacter('-');
	charList[37].SetCharacter('.');
	charList[38].SetCharacter('!');
	charList[39].SetCharacter(' ');
}