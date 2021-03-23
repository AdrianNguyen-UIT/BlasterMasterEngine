#pragma once
#include "Assets/Particles/RocketSparkle.h"
#include "Assets/Bullets/Bullet.h"

class RocketFireBullet : public Bullet
{
private:
	RECT horizontalRect;
	RECT verticalRect;
	//? To delay bullet change direction too quickly
	float currentBulletTime;
	float currentBulletTimeY;
	float changeDirectionDelayX = 500.0f;
	float changeDirectionDelayY = 20.0f;

	float currentBulletX, currentBulletY; //? To check position of current Rocket Bullet
	std::shared_ptr<Object2D> nearestEnemy;

	std::shared_ptr<RocketSparkle> rocketSparkle;

public:
	RocketFireBullet(float x = 0, float y = 0, bool pHorizontal = true, bool pIsFacingRight = true);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
private:
	void OnFollowEnemyX(boolean Direction); //? TRUE - Right, FALSE - LEFT
	void OnFollowEnemyY(boolean Direction); //? TRUE - TOP, FALSE - BOTTOM
};