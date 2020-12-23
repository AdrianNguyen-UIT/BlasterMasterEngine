#pragma once
#include "Object/Object.h"

class NormalFireBullet : public Object2D
{
private:
	RECT horizontalRect;
	RECT verticalRect;
	bool horizontal;
	bool isFacingRight;
	float runSpeed;

	int damage;

public:
	NormalFireBullet(float x = 0, float y = 0, bool pHorizontal = true, bool pIsFacingRight = true);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

private:
	void Explode();
};