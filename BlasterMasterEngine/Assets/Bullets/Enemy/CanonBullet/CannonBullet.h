#pragma once
#include "Assets/Bullets/Bullet.h"

class CannonBullet : public Bullet
{
private:
	float horizontalMove;
	float verticalMove;
	int defaultBulletSpeed = 60;
	float flyMultiplier = 3.0f;
	Direction direction;

public:
	CannonBullet(Direction pDirection, float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};