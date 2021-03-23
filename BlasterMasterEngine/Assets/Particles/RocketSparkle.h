#pragma once
#include "Object/Object.h"

class RocketSparkle : public Object2D
{
private:
	RECT horizontalRect;
	RECT verticalRect;
	bool horizontal;
	bool isFacingLeft;
	bool isFacingRight;
	bool isFacingTop;
	bool isFacingDown;

	std::shared_ptr<Animation> onLeftSide;
	std::shared_ptr<Animation> onRightSide;
	std::shared_ptr<Animation> onTopSide;
	std::shared_ptr<Animation> onDownSide;

	int damage;

public:
	//? RocketSparkle ( X, Y, LEFT, RIGHT, TOP, BOTTOM)
	RocketSparkle(float x = 0, float y = 0, bool pIsFacingLeft = false, bool pIsFacingRight = true, bool pIsFacingTop = false, bool pIsFacingDown = false);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;
	void SetIsFacingLeft(bool FacingLeftBool)
	{
		isFacingLeft = FacingLeftBool;
		isFacingRight = false;
		isFacingTop = false;
		isFacingDown = false;
	}
	void SetIsFacingRight(bool FacingRightBool)
	{
		isFacingLeft = false;
		isFacingRight = FacingRightBool;
		isFacingTop = false;
		isFacingDown = false;
	}
	void SetIsFacingTop(bool FacingTopBool)
	{
		isFacingLeft = false;
		isFacingRight = false;
		isFacingTop = FacingTopBool;
		isFacingDown = false;
	}
	void SetIsFacingDown(bool FacingDownBool)
	{
		isFacingLeft = false;
		isFacingRight = false;
		isFacingTop = false;
		isFacingDown = FacingDownBool;
	}
private:
	void Explode();
};