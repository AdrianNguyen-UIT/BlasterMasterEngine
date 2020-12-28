#pragma once
#include "Object/Object.h"


class EnemySkullBullet : public Object2D
{
private:
	bool starting;
	bool isFacingRight;
	bool isAttackingFromRight;
	float spawnBulletAt;
	float horizontalMoveAtStart = 300.0f;
	float verticalMoveAtStart = 600.0f;
	float explosionDelayTime = 3000.0f;
	std::shared_ptr<Object2D> explosion;
	std::shared_ptr<Object2D> player;
	int damage = 0;

public:
	EnemySkullBullet(float x = 0, float y = 0, bool pIsAttackingFromRight = true);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

	int GetDamage() { return damage; }

private:
	void Flip();
};

