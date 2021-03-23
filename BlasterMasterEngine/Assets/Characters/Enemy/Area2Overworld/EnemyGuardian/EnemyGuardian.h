#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyGuardian : public Enemy	
{
private:
	Direction direction;
	float runSpeed;
	bool isRightMove;
	bool isLeftMove;
	bool isDownMove;
	bool isUpMove;
	bool isNearPlayer;
	float detectingPlayerZoneX = 50.0f;
	float detectingPlayerZoneY = 50.0f;
	float changeDirectionDelay = 500.0f;
	float changeDirectionTime;
	float shootTime;
	float delayShoot = 2000.0f;
	int defaultFPS = 6;

	std::shared_ptr<Object2D> player;

public:
	EnemyGuardian(float x = 0, float y = 0, float xMove = 45.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;

private:
	void SetAnimationParameter();
	void Shoot();

};