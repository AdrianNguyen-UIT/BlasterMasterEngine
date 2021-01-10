#include "d3dpch.h"
#include "Volcano.h"
#include "Core/SceneManager/SceneManager.h"
Volcano::Volcano(float x, float y)
	: Object2D(x, y)
{
	name = "Volcano";
	tag = Tag::Default;
	spriteRenderer = GetComponent<SpriteRenderer>();
	state = State::init;
}

void Volcano::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 1.0f };
	time = 0.0f;
}

void Volcano::Update()
{
	switch (state)
	{
	case State::init:
	{
		if (time >= 2.0f)
		{
			time = 0.0f;
			state = State::sink;
		}
		else
		{
			time += Time::GetDeltaTime();
		}
	}
	break;
	case State::sink:
	{
		if (time >= 4.0f)
		{
			time = 0.0f;
			SceneManager::DestroyObject(shared_from_this());
		}
		else
		{
			transform->position.y -= 0.1f;
			time += Time::GetDeltaTime();
		}
	}
	break;
	default:
		break;
	}
}

void Volcano::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Ending_Cutscene");
	spriteRenderer->rect = { 35, 238, 59, 262 };
}
