#pragma once
#include "Assets/Characters/Enemy/Enemy.h"

class EnemyBulletHead : public Enemy
{
private:
	float horizontalMove;
	float verticalMove;
	bool isFacingRight;
	bool isFalling;
	bool isClimbing;
	bool isOnLand;
	float time;
	float reversingDelay = 300.0f;
	float defaultHorizontalMove = 40.0f;
	float defaultVerticalMove = -15.0f;
	std::shared_ptr<Object2D> player;

public:
	EnemyBulletHead(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionStay(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

	int GetDamage() { return damage; }
	void Die();

private:
	void Flip();
};

