#include "d3dpch.h"
#include "UIElement.h"

UIElement::UIElement(float x, float y)
{
	name = "UI Element";
	position = { x, y, 0.0f };
	enable = true;
	spriteRenderer = std::make_unique<SpriteRenderer>();
	spriteRenderer->InitSpriteRenderer(DeviceResources::GetDevice());
}

void UIElement::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
}

void UIElement::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void UIElement::SetName(std::string p_Name)
{
	name = p_Name;
}

void UIElement::SetColor(Color c)
{
	color = c;
}

void UIElement::AddChildUIElement(std::shared_ptr<UIElement>& child)
{
	childUIElements.emplace_back(child);
}

void UIElement::Draw(DWORD flags)
{
	if (enable)
	{
		if (spriteRenderer != NULL && spriteRenderer->enable)
		{
			RECT rect = spriteRenderer->rect;
			D3DXVECTOR3 center((float)((rect.right - rect.left) / 2), (float)((rect.bottom - rect.top) / 2), 0.0f);

			spriteRenderer->Begin(flags);
			spriteRenderer->spriteHandler->Draw(
				spriteRenderer->sprite->spriteImage,
				&rect,
				&center,
				&position,
				D3DCOLOR_RGBA(color.red, color.green, color.blue, color.alpha));
			spriteRenderer->End();
		}
	}

	for (auto child : childUIElements)
	{
		child->Draw(flags);
	}
}