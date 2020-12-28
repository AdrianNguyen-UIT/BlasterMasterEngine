#include "d3dpch.h"
#include "Canvas.h"

Canvas::Canvas()
{
	enable = true;
}

void Canvas::AddUIElement(std::shared_ptr<UIElement>& uie)
{
	uiElements.emplace_back(uie);
}

void Canvas::Start()
{
	for (std::shared_ptr<UIElement> uiElement : uiElements)
	{
		uiElement->Start();
	}
}

void Canvas::Update()
{
	for (std::shared_ptr<UIElement> uiElement : uiElements)
	{
		if (uiElement->GetEnable())
		{
			uiElement->Update();
		}
	}
}

void Canvas::Render(DWORD flags)
{
	for (std::shared_ptr<UIElement> uiElement : uiElements)
	{
		if (uiElement->GetEnable())
		{
			uiElement->Draw(flags);
		}
	}
}
