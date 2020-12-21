#pragma once
#include "Object/Object.h"

class NormalBulletExplosion : public Object2D
{
private:
	float timeLapse;
public:
	NormalBulletExplosion(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};