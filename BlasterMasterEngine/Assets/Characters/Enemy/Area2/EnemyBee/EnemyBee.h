#pragma once
#include "Assets/Characters/Enemy/Enemy.h"
class EnemyBee : public Enemy
{
private:
	float verticalMoveRange= 30.0f;
	float horizontalMoveRange= 40.0f;
	float beginningY;
	float beginningX;

	bool allowWalkingAudio;
	float audioWalkingDelay;
	float walkingTime;
	float detectingPlayerZoneX = 100.0f;
	float detectingPlayerZoneY = 100.0f;
	bool isNearPlayer;

public:
	EnemyBee(float x = 0, float y = 0, float fHorizontalMoveRange = 40.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};