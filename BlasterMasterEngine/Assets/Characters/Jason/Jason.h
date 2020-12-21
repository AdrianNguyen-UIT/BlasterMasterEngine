#pragma once
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "Object/Object.h"
class Jason : public Object2D
{
private:
	enum class State
	{
		Normal,
		CheckPointMove,
		Die
	};

private:
	float runSpeed;
	float horizontalMove;
	bool isFacingRight;
	bool isJumping;
	float fallMultiplier;

	int hitPoint;
	bool iFrame;
	std::array<Color, 4> iFrameColors;
	State state;
	std::shared_ptr<OrthographicCamera> camera;

public:
	Jason(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnCollisionStay(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnCollisionExit(std::shared_ptr<Object2D> object) override;

private:
	void Flip();
	void Shoot() {}
	void Jump();
	void MoveCameraAccordingly();
	void ApplyCameraBound();
	void SetAnimationParameter();
	void Die();
	void DoIFrame();

public:
	void TakeDamage(int damage);
};