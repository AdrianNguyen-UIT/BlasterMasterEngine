#pragma once
#include "Object/Object.h"

class SophiaCabin : public Object2D
{
public:
	SophiaCabin(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter() override;
	virtual void OnTriggerEnter() override;
};