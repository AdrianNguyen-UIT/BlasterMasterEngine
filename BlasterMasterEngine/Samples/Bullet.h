#pragma once
#include "Object/Object.h"
class Bullet : public Object2D
{
public:
	float moveSpeed;
public:
	Bullet(float x = 0, float y = 0);

	void Start();
	void Update();
	void CreateResources();
	void OnCollisionEnter();
	void OnTriggerEnter();
};

