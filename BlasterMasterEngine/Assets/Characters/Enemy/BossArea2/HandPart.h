#pragma once
#include "BossPart.h"

class HandPart : public BossPart
{
private:
	float MoveMaxX;
	float MoveMaxY;

	void ReturnLimitPosition();

	D3DXVECTOR2 GetCenterCurrentPart();
	D3DXVECTOR2 GetCenterAheadPart();
	D3DXVECTOR2 GetCenterBehindPart();
	D3DXVECTOR2 GetCenterHand();

public:
	HandPart(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;

	void MoveFollowBehindHandPart();

	std::shared_ptr<BossPart> aheadPart;
	std::shared_ptr<BossPart> behindPart;
	bool isRightHand;
};
