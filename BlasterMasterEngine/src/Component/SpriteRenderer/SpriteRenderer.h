#pragma once
#include "d3dpch.h"

struct SpriteRenderer
{
	std::shared_ptr<Sprite> sprite;
	LPD3DXSPRITE spriteHandler;
	RECT rect;
	bool enable;
	SpriteRenderer();
	~SpriteRenderer();
	HRESULT InitSpriteRenderer(LPDIRECT3DDEVICE9 d3ddev);
	void Begin(DWORD flags);
	void End();
};