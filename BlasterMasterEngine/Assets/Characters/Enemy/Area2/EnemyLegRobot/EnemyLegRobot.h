#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyLegRobot : public Enemy
{
private:
	bool isNearPlayer;
	bool isOnAir;
	bool isWaiting;
	bool goRightFirst;
	bool startWalking;
	float beginningX;
	float startJumpingAt;
	float detectingPlayerZoneX = 120.0f;
	float detectingPlayerZoneY = 30.0f;
	float horizontalMoveRange = 100.0f;
	float defaultHorizontalMove = 20.0f;
	float jumpForceX = 150.0f;
	float jumpForceY = 800.0f;
	float jumpingDelay = 450.0f;

public:
	EnemyLegRobot(float x = 0, float y = 0, bool bGoRightFirst = true, float fHorizontalMoveRange = 100.0f, float fDetectingPlayerZoneX = 120.0f, float fDetectingPlayerZoneY = 30.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};



