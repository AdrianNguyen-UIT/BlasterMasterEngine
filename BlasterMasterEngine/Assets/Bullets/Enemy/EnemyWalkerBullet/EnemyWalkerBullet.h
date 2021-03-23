#pragma once
#include "Assets/Bullets/Bullet.h"

class EnemyWalkerBullet : public Bullet
{
private:
	int defaultBulletSpeed = 60;
	Direction directionBullet;

	bool isLeftAnimation;

public:
	EnemyWalkerBullet(float x = 0, float y = 0, Direction direction = Direction::UP, bool isLeftAnimation = FALSE);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};