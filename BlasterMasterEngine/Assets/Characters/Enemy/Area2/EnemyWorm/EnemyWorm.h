#pragma once
#include "Assets/Characters/Enemy/Enemy.h"
class EnemyWorm : public Enemy
{
private:
	bool isFalling;
	bool isNearPlayer;
	float time;
	float reversingDelay = 300.0f;
	float defaultHorizontalMove = 45.0f;
	float detectingPlayerZoneX = 700.0f;
	float detectingPlayerZoneY = 80.0f;
	float audioWalkingDelay = 300.0f;
	float jumpForceY = 230.0f;
	float walkingTime;
	bool allowWalkingAudio = false;

public:
	EnemyWorm(float x = 0, float y = 0, float fdetectRange = 200.0f);
	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};