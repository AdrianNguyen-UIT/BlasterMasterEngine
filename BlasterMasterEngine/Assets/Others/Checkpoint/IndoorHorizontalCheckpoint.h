#pragma once
#include "Object/Object.h"
class IndoorHorizontalCheckpoint : public Object2D
{
public:
	IndoorHorizontalCheckpoint(float x = 0, float y = 0);

	virtual void Start() override;
};