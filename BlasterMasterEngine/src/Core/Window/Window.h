#pragma once
#include "d3dpch.h"
#include "Core/DeviceResources/DeviceResources.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Input/Input.h"
#include "Core/SceneManager/SceneManager.h"
class Window
{
public:
	Window();
	~Window() {}

	HRESULT Create(std::wstring title, UINT width, UINT height);

	HWND GetWindowHandle() { return m_HWnd; }

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT Run(std::unique_ptr<DeviceResources> &deviceResources, 
		std::unique_ptr<Renderer> &renderer, 
		std::unique_ptr<Input> &input,
		std::unique_ptr<SceneManager> &sceneManager,
		int nCmdShow);

private:
	HWND m_HWnd;
	RECT m_Rc;
	
};

static HINSTANCE m_HInstance;
static std::wstring m_WindowClassName;