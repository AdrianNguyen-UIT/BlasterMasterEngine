#pragma once
#include "Core/Canvas/UIElement/TextUI.h"
class CreditPanel : public UIElement
{
public:
	CreditPanel(const float x = 0.0f, const float y = 0.0f);

	virtual void Update() override;
	virtual void CreateResources() override;
};