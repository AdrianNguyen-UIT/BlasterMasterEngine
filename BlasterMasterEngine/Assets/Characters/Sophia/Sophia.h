#pragma once
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "BodyParts/SophiaBodyParts.h"
#include "Bullets/NormalFireBullet.h"

class Sophia : public Object2D
{
private:

	enum class State
	{
		Normal,
		CheckPointMove,
		Climb
	};

	float runSpeed;
	float horizontalMove;
	bool pointUp;
	bool isFacingRight;
	bool isJumping;
	float fallMultiplier;

	std::shared_ptr<Object2D> leftWheel;
	std::shared_ptr<Object2D> rightWheel;
	std::shared_ptr<Object2D> wheelConnector;
	std::shared_ptr<Object2D> cabin;
	std::shared_ptr<Object2D> barrel;

	std::shared_ptr<Object2D> jason;
	std::shared_ptr<Object2D> bullet;
	std::shared_ptr<Object2D> playerDeadExplosion;
	std::shared_ptr<OrthographicCamera> camera;

	State state;
public:
	Sophia(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnCollisionExit(std::shared_ptr<Object2D> object) override;

private:
	void Flip();
	void SpawnJason();
	void Shoot();
	void Jump(bool &jump);
	void MoveCameraAccordingly();
	void ApplyCameraBound();
	void SetAnimationParameter();
};