#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyLadybug : public Enemy
{
private:
	float horizontalMove;
	bool isFacingRight;
	bool isLeftCollision;
	bool isRightCollision;
	bool starting;
	int defaultFPS = 18;

public:
	EnemyLadybug(float x = 0, float y = 0, float xMove = 45.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionStay(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

private:
	void Flip();
};

