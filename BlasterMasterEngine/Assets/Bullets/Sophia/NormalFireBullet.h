#pragma once
#include "Assets/Bullets/Bullet.h"

class NormalFireBullet : public Bullet
{
private:
	RECT horizontalRect;
	RECT verticalRect;
public:
	NormalFireBullet(float x = 0, float y = 0, bool pHorizontal = true, bool pIsFacingRight = true);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};