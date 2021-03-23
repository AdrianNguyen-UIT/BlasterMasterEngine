#pragma once
#include "Object/Object.h"
class Background : public Object2D
{
public:
	Background(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void CreateResources() override;
};