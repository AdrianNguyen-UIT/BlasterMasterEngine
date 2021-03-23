#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyCrazyLadybug : public Enemy
{
private:
	bool isNearPlayer;
	bool playerIsOutRange;
	//float vectorAdjustmentFactor;
	float detectingPlayerZoneX;
	float detectingPlayerZoneY;
	float defaultHorizontalMove = 120.0f;
	float followingPlayerMultiplier = 1.0f;
	float defaultFollowingPlayerSpeed = 120.0f;

public:
	EnemyCrazyLadybug(float x = 0, float y = 0, float fdetectingPlayerZoneX = 80.0f, float fdetectingPlayerZoneY = 80.0f, float fdetectRange = 200.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};