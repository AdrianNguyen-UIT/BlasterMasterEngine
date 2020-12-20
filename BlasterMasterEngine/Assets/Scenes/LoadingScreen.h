#pragma once
#include "Core/SceneManager/Scene.h"

class LoadingScreen : public Scene
{
public:
	LoadingScreen()
	{
		name = "Loading Screen";
	}

	~LoadingScreen() {}

	virtual void CreateScene() override;
};