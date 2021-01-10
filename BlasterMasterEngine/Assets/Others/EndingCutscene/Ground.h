#pragma once
#include "Object/Object.h"
class Ground : public Object2D
{
private:
	float time;
public:
	Ground(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};