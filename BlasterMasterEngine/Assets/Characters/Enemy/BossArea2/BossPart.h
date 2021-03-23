#pragma once
#include "Object/Object.h"

class BossPart : public Object2D
{
private:
	bool isAppear;
	bool isAttack;
	bool isDie;

	float defaultVelocityX = 45.0f;
	float defaultVelocityY = 45.0f;
	int damage;

public:
	BossPart(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerStay(std::shared_ptr<Object2D> object) override;
	void Die();
	void TakeDamage(int damage);
	int GetDamage() { return damage; }

	std::shared_ptr<Object2D> ownerObj;
};
