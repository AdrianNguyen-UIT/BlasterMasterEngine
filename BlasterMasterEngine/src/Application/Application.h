#pragma once
#include "Core/DeviceResources/DeviceResources.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Time/Time.h"
#include "Core/Window/Window.h"
#include "Core/Input/Input.h"
#include "Core/SceneManager/SceneManager.h"
#include "Core/AudioMixer/AudioMixer.h"
#include "Core/FontResources/FontResources.h"
#include "Core/SpriteResources/SpriteResources.h"
class Application
{
public:
	Application();
	~Application();
	HRESULT Run(int nCmdShow);
private:
	std::unique_ptr<Window> window;
	std::unique_ptr<DeviceResources> deviceResources;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<Input> input;
	std::unique_ptr<AudioMixer> audioMixer;
	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<FontResources> fontResources;
	std::unique_ptr<SpriteResources> spriteResources;
};