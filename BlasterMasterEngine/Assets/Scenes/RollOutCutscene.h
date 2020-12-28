#pragma once
#include "Core/SceneManager/Scene.h"
class RollOutCutscene : public Scene
{
public:
	RollOutCutscene()
	{
		name = "Roll Out Cutscene";
	}

	~RollOutCutscene() {}

	virtual void CreateScene() override;
};

