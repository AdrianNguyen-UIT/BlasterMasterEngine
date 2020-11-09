#pragma once

#include <d3dpch.h>
#include "Component/SpriteRenderer/SpriteRenderer.h"

class DeviceResources
{
public:
	DeviceResources();
	~DeviceResources();

	HRESULT CreateDeviceResources(HWND hWnd);
	PDIRECT3DDEVICE9 GetDevice() { return d3ddev; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	void Present();
	LPDIRECT3DSURFACE9 LoadSurface(std::wstring filename, D3DCOLOR transcolor);
	std::shared_ptr<Sprite> LoadTexture(std::wstring filename, D3DCOLOR transcolor);
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DSURFACE9 backBuffer;
};