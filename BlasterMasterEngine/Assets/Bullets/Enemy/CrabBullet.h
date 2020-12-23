#pragma once
#include "Object/Object.h"
class CrabBullet : public Object2D
{
private:
	int damage;
public:
	CrabBullet(float x = 0, float y = 0, float scaleX = -1.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;
};