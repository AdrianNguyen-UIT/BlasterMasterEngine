#pragma once
#include "Assets/Bullets/Bullet.h"
class SmallFireBullet : public Bullet
{
public:
	SmallFireBullet(float x = 0, float y = 0, bool pIsFacingRight = true);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};