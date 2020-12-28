#pragma once
#include "Core/SceneManager/Scene.h"
class OpeningCutscene : public Scene
{
public:
	OpeningCutscene()
	{
		name = "Opening Cutscene";
	}

	~OpeningCutscene() {}

	virtual void CreateScene() override;
};