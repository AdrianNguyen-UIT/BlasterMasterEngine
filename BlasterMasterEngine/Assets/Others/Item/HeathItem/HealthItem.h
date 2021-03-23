#pragma once
#include "Object/Object.h"

class HeathPoint : public Object2D
{
private:
	RECT horizontalRect;
	RECT verticalRect;
	bool horizontal;
	bool isFacingLeft;
	bool isFacingRight;
	bool isFacingTop;
	bool isFacingDown;

	int damage;

public:
	HeathPoint(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerStay(std::shared_ptr<Object2D> object) override;
private:
	void Die();
	void IncreaseHP();
};