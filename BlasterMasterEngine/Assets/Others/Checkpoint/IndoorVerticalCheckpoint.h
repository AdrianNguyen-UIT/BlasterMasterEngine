#pragma once
#include "Object/Object.h"
class IndoorVerticalCheckpoint : public Object2D
{
public:
	IndoorVerticalCheckpoint(float x = 0, float y = 0);

	virtual void Start() override;
};