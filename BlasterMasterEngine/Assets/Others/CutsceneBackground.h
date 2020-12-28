#pragma once
#include "Object/Object.h"
class CutsceneBackground : public Object2D
{
private:
	float playTime;
	float randomTime;
	CutsceneType cutsceneType;
public:
	CutsceneBackground(float x = 0, float y = 0, CutsceneType sct = CutsceneType::None);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;

private:
	Color GenerateRandomColor();
};