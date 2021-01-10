#pragma once
#include "Object/Object.h"

class Volcano : public Object2D
{
private:
	enum class State
	{
		init,
		sink
	};

	State state;
	float time;
public:
	Volcano(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};