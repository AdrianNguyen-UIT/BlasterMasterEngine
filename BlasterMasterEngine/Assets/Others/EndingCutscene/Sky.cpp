#include "d3dpch.h"
#include "Sky.h"
#include "Core/SceneManager/SceneManager.h"
Sky::Sky(float x, float y)
	: Object2D(x, y)
{
	name = "Sky";
	tag = Tag::Default;
	spriteRenderer = GetComponent<SpriteRenderer>();
}


void Sky::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 1.0f };
	color = {148, 148, 148, 255};
	time = 0.0f;
}

void Sky::Update()
{
	if (time >= 8.5f && time < 9.0f)
	{
		color.red += 3.0f;
		color.green += 3.0f;
		color.blue += 3.0f;
		if (color.red > 255)
			color.red = 255;
		if (color.green > 255)
			color.green = 255;
		if (color.blue > 255)
			color.blue = 255;
		LOG_INFO(color.green);
	}
	else if (time >= 9.0f)
	{
		SceneManager::DestroyObject(shared_from_this());
	}
	time += Time::GetDeltaTime();

}

void Sky::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Ending_LessColor_Cutscene");
	spriteRenderer->rect = { 2, 2, 259, 139 };
}