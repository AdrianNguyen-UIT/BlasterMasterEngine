#pragma once
#include "Object/Object.h"


class EnemyWorm : public Object2D
{
private:
	float horizontalMove;
	bool isFacingRight;
	bool isFalling;
	bool isNearPlayer;
	float time;
	float reversingDelay = 300.0f;
	float defaultHorizontalMove = 45.0f;
	float detectingPlayerZoneX = 700.0f;
	float detectingPlayerZoneY = 80.0f;
	float jumpForceY = 230.0f;
	std::shared_ptr<Object2D> player;
	int damage = 0;

public:
	EnemyWorm(float x = 0, float y = 0);

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

