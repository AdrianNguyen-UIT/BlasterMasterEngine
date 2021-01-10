#include "d3dpch.h"
#include "TextUI.h"
#include "Core/FontResources/FontResources.h"
TextUI::TextUI(const float x, const float y, const std::string& str, const std::string fn, const bool& h, const D3DXVECTOR2& os)
	: UIElement(x, y), text(str), font(fn), horizontal(h), offset(os)
{
	childUIElements.reserve(text.size());
	spriteRenderer->enable = false;
}

void TextUI::Start()
{

}

void TextUI::CreateResources()
{
	if (text.size() == 0)
		return;

	if (horizontal)
	{
		float fontWidth = FontResources::GetSize(font).width + offset.x;
		float xOffset = fontWidth * (text.size() - 1) / 2.0f;
		float xPos = position.x - xOffset;
		float yPos = position.y;

		for (size_t index = 0; index < text.size(); ++index)
		{
			RECT rect = FontResources::GetRect(font, text[index]);
			std::string fontSpriteName = FontResources::GetSpriteName(font);
			std::shared_ptr<UIElement> image = std::make_shared<ImageUI>(xPos + index * fontWidth, yPos, fontSpriteName, rect);
			image->CreateResources();
			AddChildUIElement(image);
		}
	}
	else
	{
		float fontHeight = FontResources::GetSize(font).height + offset.y;
		float yOffset = fontHeight * (text.size() - 1) / 2.0f;
		float xPos = position.x;
		float yPos = position.y - yOffset;

		for (size_t index = 0; index < text.size(); ++index)
		{
			RECT rect = FontResources::GetRect(font, text[index]);
			std::string fontSpriteName = FontResources::GetSpriteName(font);
			std::shared_ptr<UIElement> image = std::make_shared<ImageUI>(xPos, yPos + index * fontHeight, fontSpriteName, rect);
			image->CreateResources();
			AddChildUIElement(image);
		}
	}
}

void TextUI::SetColor(Color c)
{
	for (auto child : childUIElements)
	{
		child->SetColor(c);
	}
}

void TextUI::SetPosition(float x, float y, float z)
{
	UIElement::SetPosition(x, y, z);

	if (horizontal)
	{
		float fontWidth = FontResources::GetSize(font).width + offset.x;
		float xOffset = fontWidth * (text.size() - 1) / 2.0f;
		float xPos = position.x - xOffset;
		float yPos = position.y;

		for (size_t index = 0; index < text.size(); ++index)
		{
			childUIElements[index]->SetPosition(xPos + index * fontWidth, yPos);
		}
	}
	else
	{
		float fontHeight = FontResources::GetSize(font).height + offset.y;
		float yOffset = fontHeight * (text.size() - 1) / 2.0f;
		float xPos = position.x;
		float yPos = position.y - yOffset;

		for (size_t index = 0; index < text.size(); ++index)
		{
			childUIElements[index]->SetPosition(xPos, yPos + index * fontHeight);
		}
	}
}

void TextUI::SetEnable(bool p_Enable)
{
	UIElement::SetEnable(p_Enable);
	for (auto child : childUIElements)
	{
		child->SetEnable(p_Enable);
	}
}
