#pragma once
#include "Object/Object.h"
class ChooseWheel : public Object2D
{
private:
	D3DXVECTOR3 firstPos;
	D3DXVECTOR3 secondPos;
public:
	ChooseWheel(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};

