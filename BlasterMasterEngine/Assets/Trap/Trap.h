#pragma once
#include "Object/Object.h"
class Trap : public Object2D
{
public:
	int damage;

public:
	Trap(float x = 0, float y = 0);

	virtual void Start() override;
	int GetDamage() { return damage; }
};