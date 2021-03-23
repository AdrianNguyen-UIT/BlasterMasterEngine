#pragma once
#include "Assets/Bullets/Bullet.h"

class BossBullet : public Bullet
{
private:
	float runSpeed;

public:
	BossBullet(float x = 0, float y = 0);
	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};