#include "d3dpch.h"
#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer()
{
	enable = true;
}

SpriteRenderer::~SpriteRenderer()
{
	/*spriteHandler->Release();*/
}

HRESULT SpriteRenderer::InitSpriteRenderer(LPDIRECT3DDEVICE9 d3ddev)
{
	return D3DXCreateSprite(d3ddev, &spriteHandler);
}

void SpriteRenderer::Begin(DWORD flags)
{
	spriteHandler->Begin(flags);
}

void SpriteRenderer::End()
{
	spriteHandler->End();
}