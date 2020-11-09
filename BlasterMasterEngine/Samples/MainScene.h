#pragma once
#include "Core/SceneManager/Scene.h"

class MainScene : public Scene
{
public:
	MainScene()
	{
		name = L"MainScene";
	}

	~MainScene() {}

	virtual void CreateScene(std::shared_ptr<DeviceResources> deviceResources) override;
};