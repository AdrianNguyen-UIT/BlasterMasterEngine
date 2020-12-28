#include "d3dpch.h"
#include "ImageUI.h"

ImageUI::ImageUI(const float& x, const float& y, const std::string& sn, const RECT& r)
	: UIElement(x, y), spriteName(sn), rect(r)
{
	name = "Image UI";
}

void ImageUI::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite(spriteName);
	spriteRenderer->rect = rect;
}
