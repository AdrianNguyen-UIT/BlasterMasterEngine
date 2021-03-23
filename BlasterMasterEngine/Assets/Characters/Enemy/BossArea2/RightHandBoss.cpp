#include "d3dpch.h"
#include "RightHandBoss.h"
#include "Core/SceneManager/SceneManager.h"

RightHandBoss::RightHandBoss(float x, float y)
	: BossPart(x, y)
{
	name = "Right Hand Boss";
}

void RightHandBoss::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Arm_Boss_Texture");
	int spriteWidth = 18;
	int spriteHeight = 32;
	KeyFrame keyFrame;
	RECT rect;
	keyFrame.position = { 0.0f,0.0f,0.0f };
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> BossHiding = std::make_shared<Animation>("Boss Hiding");
	{
		BossHiding->SetAnimationFPS(1);

		rect.left = 0;
		rect.top = 0;
		rect.right = 1;
		rect.bottom = 1;

		keyFrame.rect = rect;
		BossHiding->AddKeyFrames(keyFrame);
		animationController->AddAnimation(BossHiding);
		animationController->SetDefaultAnimation(BossHiding);
	}

	std::shared_ptr<Animation> BossDisappear = std::make_shared<Animation>("Boss Disappear");
	{
		BossDisappear->SetIsLooping(false);
		BossDisappear->SetHasExitTime(true);
		BossDisappear->SetAllowPause(false);
		BossDisappear->SetAnimationFPS(6);
		for (int index = 0; index < 18; index++)
		{
			rect.left = 138 - (spriteWidth + 7) * (index % 6);
			rect.top = 32;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			BossDisappear->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(BossDisappear);
	}

	std::shared_ptr<Animation> BossAppear = std::make_shared<Animation>("Boss Appear");
	{
		BossAppear->SetIsLooping(false);
		BossAppear->SetHasExitTime(true);
		BossAppear->SetAllowPause(false);
		BossAppear->SetAnimationFPS(6);
		for (int index = 0; index < 18; index++)
		{
			rect.left = 13 + (spriteWidth + 7) * (index % 6);
			rect.top = 32;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			BossAppear->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(BossAppear);
	}

	std::shared_ptr<Animation> BossAttack = std::make_shared<Animation>("Boss Attack");
	{
		BossAttack->SetAnimationFPS(60);
		BossAttack->SetAllowPause(true);
		rect.left = 138;
		rect.top = 32;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		keyFrame.rect = rect;

		BossAttack->AddKeyFrames(keyFrame);

		animationController->AddAnimation(BossAttack);
	}

	std::shared_ptr<Parameter<bool>> Appear = std::make_shared<Parameter<bool>>("Appear");
	{
		animationController->AddBoolParameter(Appear);
	}

	std::shared_ptr<Parameter<bool>> Attack = std::make_shared<Parameter<bool>>("Attack");
	{
		animationController->AddBoolParameter(Attack);
	}

	std::shared_ptr<Parameter<bool>> Die = std::make_shared<Parameter<bool>>("Die");
	{
		animationController->AddBoolParameter(Die);
	}

	std::shared_ptr<TransitionCondition<bool>> appearBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		appearBoolCond->SetParameter(Appear);
		appearBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> attackBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		attackBoolCond->SetParameter(Attack);
		attackBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> notAttackBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		notAttackBoolCond->SetParameter(Attack);
		notAttackBoolCond->SetValue(false);
	}

	std::shared_ptr<TransitionCondition<bool>> dieBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		dieBoolCond->SetParameter(Die);
		dieBoolCond->SetValue(true);
	}

	std::shared_ptr<Transition> hidingToAppearTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(BossHiding),
		animationController->GetAnimationIndex(BossAppear));
	{
		hidingToAppearTrans->AddBoolTransitionCondition(appearBoolCond);
		hidingToAppearTrans->AddBoolTransitionCondition(notAttackBoolCond);
		animationController->AddTransition(hidingToAppearTrans);
	}

	std::shared_ptr<Transition> appearToAttackTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(BossAppear),
		animationController->GetAnimationIndex(BossAttack));
	{
		appearToAttackTrans->AddBoolTransitionCondition(attackBoolCond);
		animationController->AddTransition(appearToAttackTrans);
	}

	std::shared_ptr<Transition> attackToDieTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(BossAttack),
		animationController->GetAnimationIndex(BossDisappear));
	{
		attackToDieTrans->AddBoolTransitionCondition(dieBoolCond);
		animationController->AddTransition(attackToDieTrans);
	}
}

void RightHandBoss::Start()
{
	BossPart::Start();
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->size = { 18.0f, 32.0f };
}

void RightHandBoss::Update()
{

}