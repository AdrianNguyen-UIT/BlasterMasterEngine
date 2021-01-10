#pragma once
#include "Core/SceneManager/Scene.h"
class Credit : public Scene
{
public:
	Credit()
	{
		name = "Credit";
	}

	~Credit() {}

	virtual void CreateScene() override;
};