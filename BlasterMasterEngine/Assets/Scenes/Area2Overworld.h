#pragma once

#include "Core/SceneManager/Scene.h"

class Area2Overworld : public Scene
{


public:
	Area2Overworld()
	{
		name = "Area2Overworld";
	}

	~Area2Overworld() {}

	virtual void CreateScene() override;
};