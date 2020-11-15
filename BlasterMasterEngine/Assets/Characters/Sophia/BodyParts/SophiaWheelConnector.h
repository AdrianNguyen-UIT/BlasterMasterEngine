#pragma once

#include "Object/Object.h"
class SophiaWheelConnector : public Object2D
{
public:
	SophiaWheelConnector(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter() override;
	virtual void OnTriggerEnter() override;
};