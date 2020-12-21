#pragma once

struct Sprite
{
	LPDIRECT3DTEXTURE9 spriteImage;

	Sprite()
	{
		spriteImage = NULL;
	}

	~Sprite()
	{
		spriteImage = NULL;
	}
	Sprite(LPDIRECT3DTEXTURE9 p_SpriteImage)
		: spriteImage(p_SpriteImage)
	{}
};

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