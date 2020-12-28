#pragma once
#include "Core/SceneManager/SceneManager.h"
class OpeningScreen : public Scene
{
public:
	OpeningScreen()
	{
		name = "Opening Screen";
	}

	~OpeningScreen() {}

	virtual void CreateScene() override;
};