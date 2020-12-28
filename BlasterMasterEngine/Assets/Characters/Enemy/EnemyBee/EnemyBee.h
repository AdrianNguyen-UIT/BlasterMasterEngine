#pragma once
#include "Object/Object.h"


class EnemyBee : public Object2D
{
private:

	float horizontalMove;
	float verticalMove;
	bool isFacingRight;
	float verticalMoveRange= 30.0f;
	float horizontalMoveRange= 40.0f;
	float beginningY;
	float beginningX;
	int damage = 0;

public:
	EnemyBee(float x = 0, float y = 0, float fHorizontalMoveRange = 40.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

	int GetDamage() { return damage; }
	void Die();

private:
	void Flip();
};

