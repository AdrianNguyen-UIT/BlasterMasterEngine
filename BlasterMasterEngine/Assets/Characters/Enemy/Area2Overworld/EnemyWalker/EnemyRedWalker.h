#pragma once
#include "Assets/Characters/Enemy/Area2Overworld/EnemyWalker/EnemyWalker.h"

class EnemyRedWalker : public EnemyWalker
{
private:
	float shootTime;
	float delayShoot = 1000.0f;

public:
	EnemyRedWalker(float x = 0, float y = 0, float xMove = 45.0f);

	virtual void Start() override;
	virtual void CreateResources() override;

private:
	void Shoot();
};