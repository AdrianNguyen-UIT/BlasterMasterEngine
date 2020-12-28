#pragma once
#include "Core/Canvas/UIElement/UIElement.h"

class ImageUI : public UIElement
{
private:
	std::string spriteName;
	RECT rect;

public:
	ImageUI(const float& x = 0.0f, const float& y = 0.0f, const std::string &sn = "", const RECT& r = { 0, 0, 0, 0 });

	virtual void CreateResources() override;
};