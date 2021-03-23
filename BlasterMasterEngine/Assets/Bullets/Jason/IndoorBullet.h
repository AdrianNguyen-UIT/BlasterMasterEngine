#pragma once
#include "Assets/Characters/Enemy/BossArea2/BossArea2.h"
#include "Assets/Bullets/Bullet.h"

class IndoorBullet : public Bullet
{
private:
	RECT horizontalRect;
	RECT verticalRect;
	Direction direction;

public:
	IndoorBullet(Direction direction, float x = 0, float y = 0);
	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;
};