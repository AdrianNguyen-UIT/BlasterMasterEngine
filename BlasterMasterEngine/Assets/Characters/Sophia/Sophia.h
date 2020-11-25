#pragma once
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "BodyParts/SophiaBodyParts.h"

class Sophia : public Object2D
{
private:
	float runSpeed;
	float horizontalMove;
	bool pointUp;
	bool isFacingRight;
	bool isJumping;
	int frameBeforeJump;
	int frameCount;
	float fallMultiplier;
	std::shared_ptr<Object2D> leftWheel;
	std::shared_ptr<Object2D> rightWheel;
	std::shared_ptr<Object2D> wheelConnector;
	std::shared_ptr<Object2D> cabin;
	std::shared_ptr<Object2D> barrel;

	std::shared_ptr<Object2D> jason;
public:
	Sophia(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter() override;
	virtual void OnTriggerEnter() override;

private:
	void Flip();
};