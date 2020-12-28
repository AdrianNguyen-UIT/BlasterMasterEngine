#include "d3dpch.h"
#include "HealthBlock.h"

HealthBlock::HealthBlock(const float& x, const float& y)
	: ImageUI(x, y)
{
	name = "Health Block";
}

void HealthBlock::Start()
{

}

void HealthBlock::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Health_Block_Texture");
	onRect = { 2, 1, 32, 18 };
	offRect = { 2, 19, 32, 36 };
	spriteRenderer->rect = onRect;
}

void HealthBlock::SetBlockState(bool on)
{
	if (on)
	{
		spriteRenderer->rect = onRect;
	}
	else
	{
		spriteRenderer->rect = offRect;
	}
}