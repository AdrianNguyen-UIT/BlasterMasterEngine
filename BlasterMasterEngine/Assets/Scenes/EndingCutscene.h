#pragma once
#include "Core/SceneManager/Scene.h"

class EndingCutscene : public Scene
{
public:
	EndingCutscene()
	{
		name = "EndingCutscene";
	}

	~EndingCutscene() {}

	virtual void CreateScene() override;
};