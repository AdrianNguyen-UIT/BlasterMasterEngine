#pragma once
#include "Object/Object.h"

class SophiaBarrel : public Object2D
{
public:
	SophiaBarrel(float x = 0, float y = 0);

	virtual void CreateResources() override;
};