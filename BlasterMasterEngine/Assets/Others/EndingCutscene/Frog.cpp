#include "d3dpch.h"
#include "Frog.h"

Frog::Frog(float x, float y)
	: Object2D(x, y)
{
	name = "Frog";
	tag = Tag::Default;
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void Frog::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 1.0f };
}

void Frog::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Ending_Cutscene");
	spriteRenderer->rect = {463, 245, 480, 258};
}
