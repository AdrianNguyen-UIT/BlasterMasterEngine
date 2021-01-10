#pragma once
#include "Object/Object.h"
#include "Object/OrthographicCamera/OrthographicCamera.h"
class CutScenePlayer : public Object2D
{
private:
	enum class EndingPhase
	{
		phase1,
		phase2,
		phase3
	};

private:
	CutsceneType cutsceneType;
	EndingPhase endingPhase;
	bool allowLoadScene;
	std::shared_ptr<OrthographicCamera> camera;
	float endingPhaseTime;
public:
	CutScenePlayer(float x = 0, float y = 0, CutsceneType cst = CutsceneType::None);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;

private:
	D3DXVECTOR3 ShakeCamera();
};