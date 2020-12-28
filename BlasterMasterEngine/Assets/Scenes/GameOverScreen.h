#pragma once
#include "Core/SceneManager/Scene.h"
class GameOverScreen : public Scene
{
public:
	GameOverScreen()
	{
		name = "Game Over Screen";
	}

	~GameOverScreen() {}

	virtual void CreateScene() override;
};