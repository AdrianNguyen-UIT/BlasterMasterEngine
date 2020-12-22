#pragma once
#include "Object/Object.h"

class Ladder : public Object2D
{
public:
	int damage;

public:
	Ladder(float x = 0, float y = 0);

	virtual void Start() override;
};