#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class Eyeball : public Enemy
{
private:
	float testY;
	bool isAttack;
	bool circleUp;
	bool forward;
	float idleStateDelay;
	float attackStateDelay;
	float currentIdleStateTime;
	float currentAttackStateTime;
	float randomDestMaxX;
	float randomDestMaxY;
	float randomDestMinX;
	float randomDestMinY;
	float centerPointX;
	float centerPointY;
	float radiant;
	float radius;
	float destX;
	float destY;

	std::shared_ptr<Object2D> player;

public:
	Eyeball(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;

private:
	void SetAnimationParameter();
	void AttackCheck();
	void Move();
	void Attack();
	void TranslateDirection(float& x, float& y, float posX, float posY);
	void TranslateDirection(float& x, float& y);
	void SetTrajectory();
};
