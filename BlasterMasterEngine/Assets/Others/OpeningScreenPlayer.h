#pragma once
#include "Object/Object.h"
class OpeningScreenPlayer : public Object2D
{
private:
	float playTime;
	bool allowLoadScene;
public:
	OpeningScreenPlayer(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};