#include "d3dpch.h"
#include "Head.h"

Head::Head(float x, float y)
	: Object2D(x, y)
{
	name = "Head";
	tag = Tag::Default;
	spriteRenderer = GetComponent<SpriteRenderer>();
	animationController = GetComponent<AnimationController>();
}

void Head::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 1.0f };
}

void Head::Update()
{
}

void Head::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Ending_Cutscene");

	KeyFrame keyFrame;
	RECT rect;

	std::shared_ptr<Animation> headIdle = std::make_shared<Animation>("Head Idle");
	{
		headIdle->SetAnimationFPS(4);

		rect = {465, 229, 480, 243};
		keyFrame.rect = rect;
		headIdle->AddKeyFrames(keyFrame);

		rect = { 482, 229, 497, 243 };
		keyFrame.rect = rect;
		headIdle->AddKeyFrames(keyFrame);

		rect = { 499, 229, 514, 243 };
		keyFrame.rect = rect;
		headIdle->AddKeyFrames(keyFrame);

		animationController->AddAnimation(headIdle);
		animationController->SetDefaultAnimation(headIdle);
	}
}
