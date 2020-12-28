#pragma once
#include "Core/Canvas/UIElement/UIElement.h"

class HealthBar : public UIElement
{
private:
	std::array<std::shared_ptr<UIElement>, 8> healthBlocks;
	std::array<std::shared_ptr<UIElement>, 3> pow;
public:
	HealthBar(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};