#pragma once
#include "Object/Object.h"
class Head : public Object2D
{
public:
	Head(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};