#pragma once
#include "Assets/Characters/Enemy/Enemy.h"
#include "Core/SceneManager/SceneManager.h"

class EnemyWalker : public Enemy
{
protected:
	Direction direction;
	float runSpeed;
	
	bool isIdle;
	bool isNearPlayer;
	
	float detectingPlayerZoneX;
	float detectingPlayerZoneY;
	float changeDirectionDelay;
	float changeDirectionTime;
	
	int defaultFPS = 6;
	std::shared_ptr<Object2D> player;

public:
	EnemyWalker(float x = 0, float y = 0, float xMove = 45.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;

protected:
	virtual void SetAnimationParameter();
};