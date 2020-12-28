#include "d3dpch.h"
#include "ChooseWheel.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Characters/PlayerHealth.h"
ChooseWheel::ChooseWheel(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Default;
	name = "Choose Wheel";
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	firstPos = { 0.0f, 0.0f, 0.0f };
	secondPos = { 0.0f, 0.0f, 0.0f };
}

void ChooseWheel::Start()
{
	firstPos.x = SceneManager::GetActiveScene()->GetActiceCamera()->GetPosition().x + SceneManager::GetActiveScene()->GetActiceCamera()->GetSize().width / 2 - 50;
	firstPos.y = SceneManager::GetActiveScene()->GetActiceCamera()->GetPosition().y - SceneManager::GetActiveScene()->GetActiceCamera()->GetSize().height / 2 + 20;
	secondPos.x = SceneManager::GetActiveScene()->GetActiceCamera()->GetPosition().x + SceneManager::GetActiveScene()->GetActiceCamera()->GetSize().width / 2 - 50;
	secondPos.y = SceneManager::GetActiveScene()->GetActiceCamera()->GetPosition().y - SceneManager::GetActiveScene()->GetActiceCamera()->GetSize().height / 2 - 20;
	transform->position = firstPos;
	transform->scale = { WINDOW_CAMERA_SCALE_X , WINDOW_CAMERA_SCALE_Y , 1.0f};
}

void ChooseWheel::Update()
{
	if (Input::GetKeyDown(KeyCode_W))
	{
		transform->position = firstPos;
	}
	else if(Input::GetKeyDown(KeyCode_S))
	{
		transform->position = secondPos;
	}

	if (Input::GetKeyDown(KeyCode_RETURN))
	{
		PlayerHealth::ResetLife();
		if (transform->position == firstPos)
		{
			SceneManager::ReloadScene("Loading Screen");
		}
		else
		{
			SceneManager::ReloadScene("Opening Screen");
		}
	}
}

void ChooseWheel::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
	int spriteWidth = 7;
	int spriteHeight = 7;
	int xOffset = 2;
	int yOffset = 2;
	KeyFrame keyFrame;
	RECT rect;

	std::shared_ptr<Animation> wheelRun = std::make_shared<Animation>("Wheel Run");
	{
		wheelRun->SetAnimationFPS(14);
		wheelRun->SetAllowBackward(true);
		for (size_t index = 0; index < 4; ++index)
		{
			rect.left = 3 + (int)index * (xOffset + spriteWidth);
			rect.top = 3 + 2 * (yOffset + spriteHeight);
			rect.right = rect.left + spriteWidth + 1;
			rect.bottom = rect.top + spriteHeight + 1;
			keyFrame.rect = rect;
			wheelRun->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(wheelRun);
		animationController->SetDefaultAnimation(wheelRun);
	}
}
