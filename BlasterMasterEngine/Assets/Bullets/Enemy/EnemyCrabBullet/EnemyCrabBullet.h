#pragma once
#include "Assets/Bullets/Bullet.h"

class EnemyCrabBullet : public Bullet
{
private:
	float horizontalMove;
	float verticalMove;
	int defaultBulletSpeed = 60;
	float flyMultiplier = 3.0f;

public:
	EnemyCrabBullet(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};