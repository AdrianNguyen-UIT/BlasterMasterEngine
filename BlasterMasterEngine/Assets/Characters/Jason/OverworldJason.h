#pragma once
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "Object/Object.h"

class OverworldJason : public Object2D
{
public:
	static int id;

private:

	enum class State
	{
		Normal,
		CheckPointMove,
		Die
	};

	bool isTouching;
	float runSpeed;
	float horizontalMove;
	float verticalMove;
	float timeBeforLoadScreen;
	bool allowToLoad;
	bool isFacingRight;
	bool isFacingUp;
	bool isMoving;
	bool isVerticalCheckPoint;

	int hitPoint;
	bool iFrame;

	std::array<Color, 4> iFrameColors;

	std::shared_ptr<OrthographicCamera> camera;

	State state;
	Direction direction;

public:
	OverworldJason(float x = 0, float y = 0);

	virtual void Start() override;
	void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnCollisionStay(std::shared_ptr<Object2D> object) override;
	virtual void OnCollisionExit(std::shared_ptr<Object2D> object) override;

private:
	void Flip();
	void Shoot();
	void Die();
	void MoveCameraAccordingly();
	void SetAnimationParameter();
	void ApplyCameraBound();
	void SetDirection();
	void DoIFrame();

public:
	void TakeDamage(int dmg);
};