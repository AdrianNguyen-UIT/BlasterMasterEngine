#pragma once
#include "Assets/Bullets/Bullet.h"
class TeleporterBullet : public Bullet
{
private:
	float flyMultiplier;
	float directionX;
	float directionY;

public:
	TeleporterBullet(float dx, float dy, float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};