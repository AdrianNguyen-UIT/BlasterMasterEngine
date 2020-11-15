#pragma once
#include "Core/DeviceResources/DeviceResources.h"
#include "Core/SceneManager/SceneManager.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	HRESULT CreateRendererResources();
	void Update();
	void Render();

private:
	void RenderBackground();
};