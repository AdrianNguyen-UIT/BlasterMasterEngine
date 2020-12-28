#pragma once
#include "Object/Object.h"

class CutScenePlayer : public Object2D
{
private:
	CutsceneType cutsceneType;
	bool allowLoadScene;
public:
	CutScenePlayer(float x = 0, float y = 0, CutsceneType cst = CutsceneType::None);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
};