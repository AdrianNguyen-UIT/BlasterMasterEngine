#pragma once
#include "Core/DeviceResources/DeviceResources.h"
#include "Core/SceneManager/SceneManager.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<DeviceResources> deviceResources);
	~Renderer();

	HRESULT CreateRendererResources();
	void Update();
	void Render();

private:
	std::shared_ptr<DeviceResources> m_deviceResources;

private:
	void RenderBackground();
};