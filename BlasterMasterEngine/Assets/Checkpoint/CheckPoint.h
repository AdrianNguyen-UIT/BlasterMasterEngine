#pragma once
#include "Object/Object.h"
class CheckPoint : public Object2D
{
public:
	CheckPoint(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void CreateResources() override;
};