#pragma once
#include "Core/DeviceResources/DeviceResources.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Time/Time.h"
#include "Core/Window/Window.h"
#include "Core/Input/Input.h"
#include "Core/SceneManager/SceneManager.h"
#include "Core/AudioMixer/AudioMixer.h"
class Application
{
public:
	Application();
	~Application();
	HRESULT Run(int nCmdShow);
private:
	std::unique_ptr<Window> window;
	std::shared_ptr<DeviceResources> deviceResources;
	std::shared_ptr<Renderer> renderer;
	std::shared_ptr<Input> input;
	std::unique_ptr<AudioMixer> audioMixer;
	std::unique_ptr<SceneManager> sceneManager;
};