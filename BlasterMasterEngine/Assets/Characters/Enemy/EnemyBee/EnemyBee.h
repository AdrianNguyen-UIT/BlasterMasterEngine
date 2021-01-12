#pragma once
#include "Assets/Characters/Enemy/Enemy.h"
class EnemyBee : public Enemy
{
private:
	float horizontalMove;
	float verticalMove;
	bool isFacingRight;
	float verticalMoveRange= 30.0f;
	float horizontalMoveRange= 40.0f;
	float beginningY;
	float beginningX;

public:
	EnemyBee(float x = 0, float y = 0, float fHorizontalMoveRange = 40.0f);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;

private:
	void Flip();
};