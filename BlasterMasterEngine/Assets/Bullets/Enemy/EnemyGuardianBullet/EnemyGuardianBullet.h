#pragma once
#include "Assets/Bullets/Bullet.h"

class EnemyGuardianBullet : public Bullet
{
private:
	int defaultBulletSpeed = 60;
	Direction directionBullet;

public:
	EnemyGuardianBullet(float x = 0, float y = 0, Direction direction = Direction::UP);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};