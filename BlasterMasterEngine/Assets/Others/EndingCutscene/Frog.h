#pragma once
#include "Object/Object.h"
class Frog : public Object2D
{
public:
	Frog(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void CreateResources() override;
};

