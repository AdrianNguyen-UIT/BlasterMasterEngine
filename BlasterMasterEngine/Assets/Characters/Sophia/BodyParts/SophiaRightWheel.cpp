#include "d3dpch.h"
#include "SophiaRightWheel.h"


SophiaRightWheel::SophiaRightWheel(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Player;
	name = "Sophia Right Wheel";
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void SophiaRightWheel::CreateResources()
{
	float scaleX = WINDOW_CAMERA_SCALE_X;
	float scaleY = WINDOW_CAMERA_SCALE_Y;
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
	int spriteWidth = 7;
	int spriteHeight = 7;
	int xOffset = 2;
	int yOffset = 2;

	KeyFrame keyFrame;
	RECT rect;

	std::shared_ptr<Animation> wheelRun = std::make_shared<Animation>("Right Wheel Run");
	{
		wheelRun->SetAnimationFPS(14);
		wheelRun->SetAllowBackward(true);

		for (size_t index = 1; index < 4; ++index)
		{
			rect.left = 3 + (int)index * (xOffset + spriteWidth);
			rect.top = 3 + 2 * (yOffset + spriteHeight);
			rect.right = rect.left + spriteWidth + 1;
			rect.bottom = rect.top + spriteHeight + 1;
			keyFrame.rect = rect;
			keyFrame.position = transform->position;
			keyFrame.scale = { scaleX, scaleY, 0.0f };
			wheelRun->AddKeyFrames(keyFrame);
		}

		rect.left = 3;
		rect.top = 21;
		rect.right = rect.left + spriteWidth + 1;
		rect.bottom = rect.top + spriteHeight + 1;
		keyFrame.rect = rect;
		wheelRun->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelRun);
		animationController->SetDefaultAnimation(wheelRun);
	}

	std::shared_ptr<Animation> wheelRunWhileUp = std::make_shared<Animation>("Right Wheel Run While Up");
	{
		wheelRunWhileUp->SetAnimationFPS(14);
		wheelRunWhileUp->SetAllowBackward(true);

		for (size_t index = 1; index < 4; ++index)
		{
			rect.left = 3 + (int)index * (xOffset + spriteWidth);
			rect.top = 3 + 2 * (yOffset + spriteHeight);
			rect.right = rect.left + spriteWidth + 1;
			rect.bottom = rect.top + spriteHeight + 1;
			keyFrame.rect = rect;
			keyFrame.position = { transform->position.x - 5.0f / scaleX, transform->position.y, 0.0f };
			wheelRunWhileUp->AddKeyFrames(keyFrame);
		}

		rect.left = 3;
		rect.top = 21;
		rect.right = rect.left + spriteWidth + 1;
		rect.bottom = rect.top + spriteHeight + 1;
		keyFrame.rect = rect;
		wheelRunWhileUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelRunWhileUp);
	}

	std::shared_ptr<Parameter<bool>> pointUp = std::make_shared<Parameter<bool>>("pointUp");
	{
		animationController->AddBoolParameter(pointUp);
	}

	std::shared_ptr<TransitionCondition<bool>> pointUpBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		pointUpBoolCond->SetParameter(pointUp);
		pointUpBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> backFromPointUpBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		backFromPointUpBoolCond->SetParameter(pointUp);
		backFromPointUpBoolCond->SetValue(false);
	}

	std::shared_ptr<Transition> normToPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelRun),
		animationController->GetAnimationIndex(wheelRunWhileUp));
	{
		normToPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(normToPointUpTrans);
	}

	std::shared_ptr<Transition> pointUpToNormTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelRunWhileUp),
		animationController->GetAnimationIndex(wheelRun));
	{
		pointUpToNormTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(pointUpToNormTrans);
	}
}

void SophiaRightWheel::Start()
{
}

void SophiaRightWheel::Update()
{
}

void SophiaRightWheel::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
}

void SophiaRightWheel::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}