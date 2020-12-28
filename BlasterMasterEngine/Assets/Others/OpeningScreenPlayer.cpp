#include "d3dpch.h"
#include "OpeningScreenPlayer.h"
#include "Core/SpriteResources/SpriteResources.h"
#include "Core/SceneManager/SceneManager.h"

OpeningScreenPlayer::OpeningScreenPlayer(float x, float y)
	: Object2D(x, y)
{
	name = "Opening Screen Player";
	tag = Tag::Default;
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void OpeningScreenPlayer::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X , WINDOW_CAMERA_SCALE_Y, 0.0f };
	playTime = 0.0f;
	allowLoadScene = true;
}

void OpeningScreenPlayer::Update()
{
	if (playTime >= 4.0f && allowLoadScene)
	{
		playTime = 0.0f;
		allowLoadScene = false;
		SceneManager::ReloadScene("Opening Cutscene");
	}
	playTime += Time::GetDeltaTime();
}

void OpeningScreenPlayer::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Opening_Screen");
	spriteRenderer->rect = {0, 0, OPENING_SCREEN_WIDTH, OPENING_SCREEN_HEIGHT};
}
