#include "d3dpch.h"
#include "Ground.h"
#include "Core/SceneManager/SceneManager.h"
Ground::Ground(float x, float y)
	: Object2D(x, y)
{
	name = "Ground";
	tag = Tag::Default;
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void Ground::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 1.0f };
	color = { 255, 50, 0, 255 };
	time = 0.0f;
}

void Ground::Update()
{
	if (time >= 8.5f && time < 9.0f)
	{
		color.green += 5.0f;
		if (color.green > 255)
			color.green = 255;
	}
	else if (time >= 9.0f)
	{
		SceneManager::DestroyObject(shared_from_this());
	}
	time += Time::GetDeltaTime();

}

void Ground::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Ending_LessColor_Cutscene");
	spriteRenderer->rect = { 2, 138, 259, 228 };
}
