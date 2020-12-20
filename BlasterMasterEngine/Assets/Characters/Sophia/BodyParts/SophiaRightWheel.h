#pragma once

#include "Object/Object.h"
class SophiaRightWheel : public Object2D
{
public:
	SophiaRightWheel(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;
};

