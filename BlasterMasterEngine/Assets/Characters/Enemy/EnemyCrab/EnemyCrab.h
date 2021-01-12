#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyCrab : public Enemy
{
private:
	float horizontalMove;
	float verticalMove;
	bool isFacingRight;
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
	std::shared_ptr<Object2D> crabBullet;

public:
	EnemyCrab(float x = 0, float y = 0, float xMove = 50.0f, float yMove = 50.0f, float fFirstAttackDelayTime = 0.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

private:
	void Flip();
};


