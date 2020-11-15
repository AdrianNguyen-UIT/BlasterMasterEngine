#pragma once
#include "Object/Object.h"

class Terrain : public Object2D
{
public:
	Terrain(float x = 0, float y = 0);

	void Start();
	void Update();
	void CreateResources();
	void OnCollisionEnter();
	void OnTriggerEnter();
};