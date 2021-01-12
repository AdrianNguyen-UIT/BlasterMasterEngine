#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemySkull : public Enemy
{
private:
	bool isFacingRight;
	bool isNearPlayer;
	bool isAbovePlayer;
	bool isAttackingFromRight;
	bool flipFlag;
	float beginningY;
	float horizontalMove;
	float verticalMove;
	float attackingAt;
	float attackingDelay = 140.0f;
	float destructionDelay = 7000.0f;
	float SpeedHor = 200.0f; //USE FOR BOTH HORIZONTAL MOVE AND VERTICAL MOVE
	float SpeedVer = 20.0f;
	float detectingPlayerZoneX = 200.0f;
	float detectingPlayerZoneY = 200.0f;
	std::shared_ptr<Object2D> skullBullet;
	std::shared_ptr<Object2D> player;

public:
	EnemySkull(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

private:
	void Flip();
};