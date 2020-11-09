#pragma once
#include "KeyCode.h"
#include "MouseButtonCode.h"

class Input
{
public:
	Input();
	~Input();

	HRESULT CreateInputResources(HWND hWnd);
	HRESULT CreateKeyboardDevice(HWND hWnd);
	HRESULT CreateMouseDevice(HWND hWnd);

	void GetMouse();
	void GetKeyboard();

	static float GetMouseX();
	static float GetMouseY();
	static float GetMouseZ();
	static bool GetMouseButtonDown(int button);
	static bool GetMouseButton(int button);
	static bool GetKey(int keyCode);
	static bool GetKeyDown(int keyCode);

private:
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 dimouse;
	LPDIRECTINPUTDEVICE8 dikeyboard;

	//State
	static DIMOUSESTATE2 currentMouseState;
	static DIMOUSESTATE2 previousMouseState;
	static std::array<BYTE, 256> previousKeyState;
	static std::array<BYTE, 256> currentKeyState;

private:
	void ReleaseMouse();
	void ReleaseKeyboard();
};