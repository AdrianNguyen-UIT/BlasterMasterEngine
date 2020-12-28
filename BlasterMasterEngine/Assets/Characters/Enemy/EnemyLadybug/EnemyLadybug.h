#pragma once
#include "Object/Object.h"

class EnemyLadybug : public Object2D
{
private:
	float horizontalMove;
	bool isFacingRight;
	bool isLeftCollision;
	bool isRightCollision;
	bool starting;
	int defaultFPS = 18;
	int damage = 0;

public:
	EnemyLadybug(float x = 0, float y = 0, float xMove = 45.0f);

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

