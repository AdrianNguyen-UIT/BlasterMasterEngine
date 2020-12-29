#pragma once
#include "Object/Object.h"


class EnemyBulletHead : public Object2D
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
	int damage = 0;

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
