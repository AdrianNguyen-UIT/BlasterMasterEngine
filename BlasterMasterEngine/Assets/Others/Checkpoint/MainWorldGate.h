#pragma once
#include "Object/Object.h"
class MainWorldGate : public Object2D
{
public:
	MainWorldGate(float x = 0, float y = 0);
	virtual void Start() override;
};