#pragma once
#include "Core/SceneManager/Scene.h"

class Area2 : public Scene
{
public:
	Area2()
	{
		name = "Area2";
	}

	~Area2() {}

	virtual void CreateScene() override;
};