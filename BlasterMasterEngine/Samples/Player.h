#pragma once
#include "Object/Object.h"
#include "Object/OrthographicCamera/OrthographicCamera.h"
class Player : public Object2D
{
private:
	float runSpeed;
	float horizontalMove;
	std::shared_ptr<Object2D> copy;
	bool isFacingRight;

public:
	Player(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter() override;
	virtual void OnTriggerEnter() override;

private:
	void Flip();
};