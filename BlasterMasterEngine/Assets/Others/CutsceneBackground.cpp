#include "d3dpch.h"
#include "CutsceneBackground.h"

CutsceneBackground::CutsceneBackground(float x, float y, CutsceneType cst)
	: Object2D(x, y), cutsceneType(cst)
{
	name = "Cutscene Background";
	tag = Tag::Default;
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void CutsceneBackground::Start()
{
	playTime = 0.0f;
	randomTime = 0.0f;
}

void CutsceneBackground::Update()
{
	if (cutsceneType == CutsceneType::None)
	{
		if (randomTime >= 2.5f && randomTime <= 4.0f)
		{
			color = { 80, 53, 240, 255 };
			return;
		}
		randomTime += Time::GetDeltaTime();
	}

	if (playTime >= 0.06f)
	{
		color = GenerateRandomColor();
		playTime = 0.0f;
	}
	playTime += Time::GetDeltaTime();

}

void CutsceneBackground::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("White_Background");
	spriteRenderer->rect = { 0, 0, 700, 500 };
}

Color CutsceneBackground::GenerateRandomColor()
{
	Color color;
	std::random_device rdev{};
	std::default_random_engine e{ rdev() };
	std::uniform_int_distribution<> dis(0, 255);
	color.red = dis(e);
	color.green = dis(e);
	color.blue = dis(e);
	return color;
}
