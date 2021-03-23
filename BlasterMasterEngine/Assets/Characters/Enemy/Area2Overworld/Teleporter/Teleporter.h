#pragma once
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "Assets/Characters/Enemy/Enemy.h"

class Teleporter : public Enemy
{
private:
	int intervalAttack;
	float detectZoneX;
	float detectZoneY;
	float transformAnimationDelay;
	float transformCurrentTime;
	float attackStateCurrentTime;
	float attackCurrentTime;
	float teleportDistance;
	float attackStateDelay;
	float attackDelay;
	float teleTime;
	float teleCurrent;
	float idleDelay;
	float currentIdleDelay;
	bool isDetect;
	bool isAttacking;
	bool isAttack;
	bool isTele;

	std::shared_ptr<Object2D> player;

public:
	Teleporter(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;

private:
	void SetAnimationParameter();
	void AttackCheck();
	void Tele();
	void Attack();
	void TranslateDirection(float& x, float& y);
};
