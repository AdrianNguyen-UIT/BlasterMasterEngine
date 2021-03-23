#pragma once
#include "BossPart.h"

class BodyBoss : public BossPart
{
private:

public:
	BodyBoss(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};
