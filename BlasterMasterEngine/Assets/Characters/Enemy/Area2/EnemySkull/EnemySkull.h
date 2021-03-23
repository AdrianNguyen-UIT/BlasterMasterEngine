#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemySkull : public Enemy
{
private:
	bool isNearPlayer;
	bool isAbovePlayer;
	bool isAttackingFromRight;
	bool flipFlag;
	float beginningY;
	float attackingAt;
	float attackingDelay = 140.0f;
	float destructionDelay = 7000.0f;
	float SpeedHor = 200.0f; //USE FOR BOTH HORIZONTAL MOVE AND VERTICAL MOVE
	float SpeedVer = 180.0f;
	float detectingPlayerZoneX = 200.0f;
	float detectingPlayerZoneY = 200.0f;

public:
	EnemySkull(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};