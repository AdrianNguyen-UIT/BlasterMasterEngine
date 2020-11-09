#include "d3dpch.h"
#include "Input.h"

DIMOUSESTATE2 Input::currentMouseState = {};
DIMOUSESTATE2 Input::previousMouseState = {};
std::array<BYTE, 256> Input::previousKeyState = {};
std::array<BYTE, 256> Input::currentKeyState = {};

Input::Input()
{
	dinput = NULL;
	dimouse = NULL;
	dikeyboard = NULL;
}

Input::~Input()
{
	ReleaseMouse();
	ReleaseKeyboard();
}

HRESULT Input::CreateInputResources(HWND hWnd)
{
	HRESULT hr = S_OK;
	hr = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create Direct Input resources!");
	}
	return hr;
}

HRESULT Input::CreateKeyboardDevice(HWND hWnd)
{
	HRESULT hr = S_OK;

	hr = dinput->CreateDevice(GUID_SysKeyboard,
		&dikeyboard, NULL);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create keyboard device!");
		return hr;
	}

	hr = dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to set data format!");
		return hr;
	}

	hr = dikeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to set cooperative level!");
		return hr;
	}

	hr = dikeyboard->Acquire();
	if (FAILED(hr))
	{
		if (hr == E_ACCESSDENIED)
		{
			hr = S_OK;
		}
		else
		{
			__ASSERT(false, "Unable to acquire keyboard!");
		}
		return hr;
	}
	return hr;
}

HRESULT Input::CreateMouseDevice(HWND hWnd)
{
	HRESULT hr = S_OK;

	ZeroMemory(&currentMouseState, sizeof(currentMouseState));
	ZeroMemory(&previousMouseState, sizeof(previousMouseState));

	hr = dinput->CreateDevice(GUID_SysMouse,
		&dimouse, NULL);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to create mouse device!");
		return hr;
	}

	hr = dimouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to set data format!");
		return hr;
	}

	hr = dimouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		__ASSERT(false, "Unable to set cooperative level!");
		return hr;
	}

	hr = dimouse->Acquire();
	if (FAILED(hr))
	{
		if (hr == E_ACCESSDENIED)
		{
			hr = S_OK;
		}
		else
		{
			__ASSERT(false, "Unable to acquire keyboard!");
		}
		return hr;
	}
	return hr;
}

void Input::ReleaseMouse()
{
	if (dimouse != NULL)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}
}

void Input::ReleaseKeyboard()
{
	if (dikeyboard != NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
}

void Input::GetMouse()
{
	previousMouseState = currentMouseState;
	HRESULT hr = dimouse->GetDeviceState(sizeof(DIMOUSESTATE2), (LPVOID)&currentMouseState);
	if (FAILED(hr)) 
	{
		ZeroMemory(&currentMouseState, sizeof(currentMouseState));
		dimouse->Acquire();
	}
}

void Input::GetKeyboard()
{
	previousKeyState = currentKeyState;
	HRESULT hr = dikeyboard->GetDeviceState(sizeof(currentKeyState), (LPVOID)&currentKeyState);
	if (FAILED(hr))
	{
		dikeyboard->Acquire();
	}
}

float Input::GetMouseX()
{
	return (float)currentMouseState.lX;
}

float Input::GetMouseY()
{
	return (float)currentMouseState.lY;
}

float Input::GetMouseZ()
{
	return (float)currentMouseState.lZ;
}

bool Input::GetMouseButtonDown(int button)
{
	return ((currentMouseState.rgbButtons[button] & 0x80) && !(previousMouseState.rgbButtons[button] & 0x80));
}

bool Input::GetKeyDown(int keyCode)
{
	return ((currentKeyState[keyCode] & 0x80) && !(previousKeyState[keyCode] & 0x80));
}

bool Input::GetMouseButton(int button)
{
	return (currentMouseState.rgbButtons[button] & 0x80);
}

bool Input::GetKey(int keyCode)
{
	return (currentKeyState[keyCode] & 0x80);
}