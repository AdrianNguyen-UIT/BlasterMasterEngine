#pragma once
#include "Object/Object.h"

class BreakWallBulletItem : public Object2D
{
private:

public:
	BreakWallBulletItem(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerStay(std::shared_ptr<Object2D> object) override;
private:
	void Die();
};