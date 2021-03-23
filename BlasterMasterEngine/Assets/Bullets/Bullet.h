#pragma once
#include "Object/Object.h"

class Bullet : public Object2D
{
protected:
	bool horizontal;
	bool isFacingRight;
	float runSpeed;

	int damage;

public:
	Bullet(float x = 0, float y = 0, bool pHorizontal = true, bool pIsFacingRight = true);

	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;

protected:
	void Explode();
};