#pragma once
#include "Core/Canvas/UIElement/ImageUI.h"

class HealthBlock : public ImageUI
{
private:
	RECT onRect;
	RECT offRect;

public:
	HealthBlock(const float& x = 0.0f, const float& y = 0.0f);

	virtual void Start() override;
	virtual void CreateResources() override;

	void SetBlockState(bool on);
};