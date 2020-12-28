#pragma once

#include <d3dpch.h>
#include "Component/SpriteRenderer/SpriteRenderer.h"

class DeviceResources
{
public:
	DeviceResources();
	~DeviceResources();

	HRESULT CreateDeviceResources(HWND hWnd);
	static LPDIRECT3DDEVICE9 GetDevice() { return d3ddev; }
	static LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	void Present();
	static LPDIRECT3DSURFACE9 LoadSurface(std::wstring filename, D3DCOLOR transcolor);
	static std::shared_ptr<Sprite> LoadTexture(std::wstring filename, D3DCOLOR transcolor);

private:
	static LPDIRECT3D9 d3d;
	static LPDIRECT3DDEVICE9 d3ddev;
	static LPDIRECT3DSURFACE9 backBuffer;
};

