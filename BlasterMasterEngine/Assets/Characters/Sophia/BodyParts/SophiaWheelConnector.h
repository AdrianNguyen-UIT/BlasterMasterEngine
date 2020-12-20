#pragma once

#include "Object/Object.h"
class SophiaWheelConnector : public Object2D
{
public:
	SophiaWheelConnector(float x = 0, float y = 0);

	virtual void CreateResources() override;
};