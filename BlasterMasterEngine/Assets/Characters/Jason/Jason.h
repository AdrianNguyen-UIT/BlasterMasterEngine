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
		Die,
		Climbing
	};

private:
	float runSpeed;
	float horizontalMove;
	float verticalMove;
	bool isFacingRight;
	bool isJumping;
	bool readyToClimb;
	bool isClimbing;
	float climbSpeed;
	bool isCrouching;
	float fallMultiplier;
	float speedMulti;

	bool iFrame;
	std::array<Color, 4> iFrameColors;

	float timeBeforLoadScreen;
	bool allowToLoad;

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
	void Shoot();
	void Jump();
	void Crouch(bool enable, float speedScalar = 0.2f);
	void MoveCameraAccordingly();
	void ApplyCameraBound();
	void SetAnimationParameter();
	void Die();
	void DoIFrame();


	bool ControlHorizontalMove(bool onGround = true);
	bool ControlVerticalMove();
public:
	void TakeDamage(int damage);
};