#pragma once
#include "BossPart.h"

class LeftHandBoss : public BossPart
{
private:

public:
	LeftHandBoss(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;


};
