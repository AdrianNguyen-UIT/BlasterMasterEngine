#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyBulletHead : public Enemy
{
private:
	bool isFalling;
	bool isClimbing;
	bool isOnLand;
	float time;
	float reversingDelay = 300.0f;
	float defaultHorizontalMove = 40.0f;
	float defaultVerticalMove = -15.0f;

public:
	EnemyBulletHead(float x = 0, float y = 0, float fdetectRange = 155.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};