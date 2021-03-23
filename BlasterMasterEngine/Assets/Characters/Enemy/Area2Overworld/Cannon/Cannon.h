#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class Cannon : public Enemy
{
private:

	float afterAttackDelayTime;
	float attackingDelayTime;
	float startWaitinAfterAttackgAt;
	float startAttackingAt;

	bool isVerticalAttack;
	bool isAttacking;
	bool isWaitingAfterAttack;

	std::shared_ptr<Object2D> bullet_1;
	std::shared_ptr<Object2D> bullet_2;

public:
	Cannon(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;

private:
	void SetAnimationParameter();
	void AttackCheck();
	void Attack();
};
