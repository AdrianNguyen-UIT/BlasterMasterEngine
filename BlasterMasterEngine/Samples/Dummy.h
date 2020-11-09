#pragma once
#include "Object/Object.h"

class Dummy : public Object2D
{
public:
	Dummy(float x = 0, float y = 0);

	void Start();
	void Update();
	void CreateResources();
	void OnCollisionEnter();
	void OnTriggerEnter();
};