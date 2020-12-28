#pragma once
#include "UIElement/UIElement.h"

class Canvas
{
private:
	std::vector<std::shared_ptr<UIElement>> uiElements;
	bool enable;

public:
	Canvas();

	void AddUIElement(std::shared_ptr<UIElement>& uie);

	void Start();
	void Update();
	void Render(DWORD flags);

	void SetEnable(bool p_Enable) { enable = p_Enable; }
	bool GetEnable() { return enable; }
};