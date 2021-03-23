#pragma once
#include "BossPart.h"

class RightHandBoss : public BossPart
{
private:

public:
	RightHandBoss(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};
