#pragma once
#include "Assets/Bullets/Bullet.h"

class EnemySkullBullet : public Bullet
{
private:
	bool starting;
	bool isFacingRight;
	bool isAttackingFromRight;
	float spawnBulletAt;
	float horizontalMoveAtStart = 300.0f;
	float verticalMoveAtStart = 600.0f;
	float explosionDelayTime = 3000.0f;

public:
	EnemySkullBullet(float x = 0, float y = 0, bool pIsAttackingFromRight = true);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};