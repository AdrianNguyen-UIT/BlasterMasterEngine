#include "d3dpch.h"
#include "BodyBoss.h"

#include "Core/SceneManager/SceneManager.h"

BodyBoss::BodyBoss(float x, float y)
	: BossPart(x, y)
{
	name = "Body Boss";
}

void BodyBoss::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Body_Boss_Texture");
	int spriteWidth = 60;
	int spriteHeight = 68;
	KeyFrame keyFrame;
	RECT rect;
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
		int i;
		BossDisappear->SetIsLooping(false);
		BossDisappear->SetHasExitTime(true);
		BossDisappear->SetAllowPause(false);
		BossDisappear->SetAnimationFPS(6);
		for (int index = 0; index < 14; index++)
		{
			i = (index % 7);
			if (i == 6)
			{
				rect.left = 0;
				rect.top = 0;
				rect.right = 1;
				rect.bottom = 1;
			}
			else
			{
				rect.left = 4 + (spriteWidth + 4);
				rect.top = 4 + ((index % 6) * (spriteHeight + 4) * 2);
				rect.right = rect.left + spriteWidth;
				rect.bottom = rect.top + spriteHeight;
			}
			keyFrame.rect = rect;
			BossDisappear->AddKeyFrames(keyFrame);
		}
		for (int index = 0; index < 2; index++)
		{
			rect.left = 4 + (spriteWidth + 4);
			rect.top = 4 + ((index % 6) * (spriteHeight + 4) * 2);
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;

			keyFrame.rect = rect;
			BossDisappear->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(BossDisappear);
	}

	std::shared_ptr<Animation> BossAppear = std::make_shared<Animation>("Boss Appear");
	{
		int i;
		BossAppear->SetIsLooping(false);
		BossAppear->SetHasExitTime(true);
		BossAppear->SetAllowPause(false);
		BossAppear->SetAnimationFPS(6);
		for (int index = 0; index < 14; index++)
		{
			i = (index % 7);
			if (i == 6)
			{
				rect.left = 0;
				rect.top = 0;
				rect.right = 1;
				rect.bottom = 1;
			}
			else
			{
				rect.left = 4 + (spriteWidth + 4);
				rect.top = 796 - (i * (spriteHeight + 4) * 2);
				rect.right = rect.left + spriteWidth;
				rect.bottom = rect.top + spriteHeight;
			}

			keyFrame.rect = rect;
			BossAppear->AddKeyFrames(keyFrame);
		}

		for (int index = 0; index < 5; index++)
		{
			rect.left = 4 + (spriteWidth + 4);
			rect.top = 796 - ((index % 6) * (spriteHeight + 4) * 2);
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;

			keyFrame.rect = rect;
			BossAppear->AddKeyFrames(keyFrame);
		}

		animationController->AddAnimation(BossAppear);
	}

	std::shared_ptr<Animation> BossAttack = std::make_shared<Animation>("Boss Attack");
	{
		BossAttack->SetAnimationFPS(5);
		BossAppear->SetAllowPause(true);
		for (int index = 0; index < 4; index++)
		{
			rect.left = 4 + index * (spriteWidth + 4);
			rect.top = 148 + (index % 2 == 0 ? +1 : 0);
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			BossAttack->AddKeyFrames(keyFrame);
		}
		for (int index = 0; index < 4; index++)
		{
			rect.left = 4 + index * (spriteWidth + 4);
			rect.top = 220 + (index % 2 == 0 ? +1 : 0);
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			BossAttack->AddKeyFrames(keyFrame);
		}
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

void BodyBoss::Start()
{
	BossPart::Start();
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->size = { 60.0f, 68.0f };
}

void BodyBoss::Update()
{

}