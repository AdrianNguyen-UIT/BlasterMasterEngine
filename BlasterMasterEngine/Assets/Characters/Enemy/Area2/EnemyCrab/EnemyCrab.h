#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyCrab : public Enemy
{
private:
	bool isWaitingAfterAttack;
	bool isAttacking;
	float startWaitinAfterAttackgAt;
	float startAttackingAt;
	bool firstAttack;
	float firstAttackDelayTime;
	float afterAttackDelayTime = 1200.0f;
	//1200
	float attackingDelayTime = 250.0f;
	//250

public:
	EnemyCrab(float x = 0, float y = 0, float xMove = 50.0f, float yMove = 50.0f, float fFirstAttackDelayTime = 0.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};


