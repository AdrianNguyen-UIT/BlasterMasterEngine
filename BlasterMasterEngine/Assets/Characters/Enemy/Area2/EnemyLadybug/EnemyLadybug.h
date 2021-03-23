#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyLadybug : public Enemy
{
private:
	bool isLeftCollision;
	bool isRightCollision;
	bool starting;
	int defaultFPS = 18;

public:
	EnemyLadybug(float x = 0, float y = 0, float xMove = 45.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};

