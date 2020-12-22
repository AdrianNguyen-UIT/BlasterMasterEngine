#pragma once
#include "Object/Object.h"
class SmallFireBullet : public Object2D
{
private:
	bool isFacingRight;
	float runSpeed;

public:
	SmallFireBullet(float x = 0, float y = 0, bool pIsFacingRight = true);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

private:
	void Explode();
};