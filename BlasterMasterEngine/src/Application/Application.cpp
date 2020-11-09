#include "d3dpch.h"
#include "Application.h"

Application::Application()
{
	window = std::make_unique<Window>();
	deviceResources = std::make_shared<DeviceResources>();
	renderer = std::make_shared<Renderer>(deviceResources);
    sceneManager = std::make_unique<SceneManager>(deviceResources);
    input = std::make_shared<Input>();
    audioMixer = std::make_unique<AudioMixer>();
}

Application::~Application()
{
}

HRESULT Application::Run(int nCmdShow)
{
	HRESULT hr = S_OK;

    LOG_TRACE("Creating window...");
	hr = window->Create(WINDOW_TITLE, (UINT)WIDTH, (UINT)HEIGHT);

    if (SUCCEEDED(hr))
    {
        LOG_INFO("SUCCESS!");

        LOG_TRACE("Creating device resources...");
        hr = deviceResources->CreateDeviceResources(window->GetWindowHandle());
        if (FAILED(hr))
            __ASSERT(false, "FAIL!");
        LOG_INFO("SUCCESS!");

        LOG_TRACE("Creating Direct Input resources....");
        hr = input->CreateInputResources(window->GetWindowHandle());
        if (FAILED(hr))
            __ASSERT(false, "FAIL!");
        LOG_INFO("SUCCESS!");

        LOG_TRACE("Creating keyboard device....");
        hr = input->CreateKeyboardDevice(window->GetWindowHandle());
        if (FAILED(hr))
            __ASSERT(false, "FAIL!");
        LOG_INFO("SUCCESS!");

        LOG_TRACE("Creating mouse device....");
        hr = input->CreateMouseDevice(window->GetWindowHandle());
        if (FAILED(hr))
            __ASSERT(false, "FAIL!");
        LOG_INFO("SUCCESS!");

        LOG_TRACE("Creating audio mixer resources....");
        hr = audioMixer->CreateAudioMixerResources(window->GetWindowHandle());
        if (FAILED(hr))
            __ASSERT(false, "FAIL!");
        LOG_INFO("SUCCESS!");

        LOG_TRACE("Creating scene manager....");
        hr = sceneManager->CreateScenesResources();
        if (FAILED(hr))
            __ASSERT(false, "FAIL!");
        LOG_INFO("SUCCESS!");

        LOG_TRACE("Creating renderer....");
        hr = renderer->CreateRendererResources();
        if (FAILED(hr))
            __ASSERT(false, "FAIL!");
        LOG_INFO("SUCCESS!");

        LOG_INFO("Run");
        hr = window->Run(deviceResources, renderer, input, nCmdShow);
    }
    else
    {
        __ASSERT(false, "FAIL!");
    }
    return hr;
}