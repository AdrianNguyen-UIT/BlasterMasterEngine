#pragma once
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "Object/Object.h"

class Jason : public Object2D
{
private:
	float runSpeed;
	float horizontalMove;
	bool isFacingRight;
	bool isJumping;
	float fallMultiplier;

public:
	Jason(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter() override;
	virtual void OnTriggerEnter() override;

private:
	void Flip();
};