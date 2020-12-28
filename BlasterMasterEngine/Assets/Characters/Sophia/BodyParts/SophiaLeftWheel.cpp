#include "d3dpch.h"
#include "SophiaLeftWheel.h"

SophiaLeftWheel::SophiaLeftWheel(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Player;
	name = "Sophia Left Wheel";
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void SophiaLeftWheel::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
	float scaleX = WINDOW_CAMERA_SCALE_X;
	float scaleY = WINDOW_CAMERA_SCALE_Y;
	int spriteWidth = 7;
	int spriteHeight = 7;
	int xOffset = 2;
	int yOffset = 2;
	KeyFrame keyFrame;
	RECT rect;

	std::shared_ptr<Animation> wheelRun = std::make_shared<Animation>("Left Wheel Run");
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
			keyFrame.position = transform->position;
			keyFrame.scale = { scaleX, scaleY, 0.0f };
			wheelRun->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(wheelRun);
		animationController->SetDefaultAnimation(wheelRun);
	}

	std::shared_ptr<Animation> wheelRunWhileUp = std::make_shared<Animation>("Left Wheel Run While Up");
	{
		wheelRunWhileUp->SetAnimationFPS(14);
		wheelRunWhileUp->SetAllowBackward(true);
		for (size_t index = 0; index < 4; ++index)
		{
			rect.left = 3 + (int)index * (xOffset + spriteWidth);
			rect.top = 3 + 2 * (yOffset + spriteHeight);
			rect.right = rect.left + spriteWidth + 1;
			rect.bottom = rect.top + spriteHeight + 1;
			keyFrame.rect = rect;
			keyFrame.position = { transform->position.x + 5.0f / scaleX, transform->position.y, 0.0f };
			wheelRunWhileUp->AddKeyFrames(keyFrame);
		}
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

	std::shared_ptr<Transition> NormToPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelRun),
		animationController->GetAnimationIndex(wheelRunWhileUp));
	{
		NormToPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(NormToPointUpTrans);
	}

	std::shared_ptr<Transition> pointUpToNormTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelRunWhileUp),
		animationController->GetAnimationIndex(wheelRun));
	{
		pointUpToNormTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(pointUpToNormTrans);
	}
}

void SophiaLeftWheel::Start()
{

}

void SophiaLeftWheel::Update()
{
	//LOG_INFO("{0}", animationController->GetCurrentAnimation()->GetName());
}

void SophiaLeftWheel::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
}

void SophiaLeftWheel::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}