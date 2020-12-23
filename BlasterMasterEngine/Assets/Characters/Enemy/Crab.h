#pragma once
#include "Object/Object.h"

class Crab : public Object2D
{
private:
	bool isShooting;
	std::array<Color, 4> iFrameColors;
	bool iFrame;
	float shootingTime;
	float minShootingTime;
	float maxShootingTime;
	float shootingInterval;
	float iFrameTime;
	int iFrameColorIndex;
	bool start;

	int hitPoint;
	int damage;
public:
	Crab(float x = 0, float y = 0);
	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;

	void TakeDamage(int p_Damage);
private:
	void DoIFrame();
	void GenerateRandomTimeToShoot();
	void Shoot();
	void Die();
};