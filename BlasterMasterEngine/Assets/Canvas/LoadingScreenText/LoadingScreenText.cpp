#include "d3dpch.h"
#include "LoadingScreenText.h"
#include "Assets/Characters/PlayerHealth.h"
#include "Core/SceneManager/SceneManager.h"

LoadingScreenText::LoadingScreenText(const float x, const float y)
	: TextUI(x, y, "", "Health Bar Font")
{
	allowToLoad = true;
	timeBeforeLoad = 0.0f;
}

void LoadingScreenText::Update()
{
	if (timeBeforeLoad >= 1.5f && allowToLoad)
	{
		allowToLoad = false;
		timeBeforeLoad = 0.0f;
		SceneManager::ReloadScene("Area2");
	}
	timeBeforeLoad += Time::GetDeltaTime();
}

void LoadingScreenText::CreateResources()
{
	text = "LEFT " + std::to_string(PlayerHealth::GetPlayerLife());
	TextUI::CreateResources();
}
