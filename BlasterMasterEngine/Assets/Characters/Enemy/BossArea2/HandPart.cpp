#include "d3dpch.h"
#include "HandPart.h"



#include "Assets/Characters/Enemy/BossArea2/BodyBoss.h"
#include "Assets/Characters/Enemy/BossArea2/LeftHandBoss.h"
#include "Assets/Characters/Enemy/BossArea2/RightHandBoss.h"
#include "Core/SceneManager/SceneManager.h"

HandPart::HandPart(float x, float y)
	: BossPart(x, y)
{
	name = "Hand Part";
	isRightHand = true;
}

void HandPart::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Arm_Boss_Texture");
	int spriteWidth = 16;
	int spriteHeight = 17;
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
			rect.left = 136 - (spriteWidth + 9) * (index % 6);
			rect.top = 14;
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
			rect.left = 11 + (spriteWidth + 9) * (index % 6);
			rect.top = 14;
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
		rect.left = 136;
		rect.top = 14;
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

void HandPart::Start()
{
	BossPart::Start();
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->size = { 16.0f, 17.0f };
	MoveMaxX = 16;
	MoveMaxY = 18;
}

void HandPart::Update()
{

}

void HandPart::ReturnLimitPosition()
{
	D3DXVECTOR2 center_AheadPart;
	D3DXVECTOR2 center_CurrentPart = GetCenterCurrentPart();

	center_AheadPart = GetCenterAheadPart();

	float distanceX = center_CurrentPart.x - center_AheadPart.x;
	float distanceY = center_CurrentPart.y - center_AheadPart.y;

	if (abs(distanceX) > MoveMaxX)
	{
		transform->position.x = center_AheadPart.x + MoveMaxX * (distanceX / abs(distanceX));
	}

	if (abs(distanceY) > MoveMaxY)
	{
		transform->position.y = center_AheadPart.y + MoveMaxY * (distanceY / abs(distanceY));
	}

	if (!(std::dynamic_pointer_cast<RightHandBoss>(behindPart) != nullptr || std::dynamic_pointer_cast<LeftHandBoss>(behindPart) != nullptr))
	{
		if ((isRightHand && (center_AheadPart.x - center_CurrentPart.x > 0)) ||
			(!isRightHand && (center_AheadPart.x - center_CurrentPart.x < 0)))
		{
			transform->position.x = center_AheadPart.x;
		}
	}

	center_CurrentPart = GetCenterCurrentPart();

	if (std::dynamic_pointer_cast<RightHandBoss>(behindPart) != nullptr || std::dynamic_pointer_cast<LeftHandBoss>(behindPart) != nullptr)
	{
		D3DXVECTOR2 center_BehindPart = GetCenterBehindPart();
		float distanceX_CurrentToBehind = center_BehindPart.x - center_CurrentPart.x;
		float distanceY_CurrentToBehind = center_BehindPart.y - center_CurrentPart.y;
		if (abs(distanceX) > MoveMaxX)
		{
			behindPart->transform->position.x = center_CurrentPart.x + MoveMaxX * (distanceX_CurrentToBehind / abs(distanceX_CurrentToBehind));
		}
		if (abs(distanceY) > MoveMaxY)
		{
			behindPart->transform->position.y = center_CurrentPart.y + MoveMaxY * (distanceY_CurrentToBehind / abs(distanceY_CurrentToBehind)) - 8.0f;
		}
		center_CurrentPart = GetCenterCurrentPart();
		return;
	}

	if (behindPart != nullptr)
	{
		std::dynamic_pointer_cast<HandPart>(behindPart)->ReturnLimitPosition();
	}

}

void HandPart::MoveFollowBehindHandPart()
{
	D3DXVECTOR2 center_AheadPart;
	D3DXVECTOR2 center_BehindPart;
	D3DXVECTOR2 center_CurrentPart = GetCenterCurrentPart();

	bool isFirstPart = false; // part near body
	bool isLastPart = false; // part near hand

	if (std::dynamic_pointer_cast<RightHandBoss>(behindPart) != nullptr || std::dynamic_pointer_cast<LeftHandBoss>(behindPart) != nullptr)
	{
		isLastPart = true;
	}
	if (std::dynamic_pointer_cast<BodyBoss>(aheadPart) != nullptr)
	{
		isFirstPart = true;
	}

	center_AheadPart = GetCenterAheadPart();
	center_BehindPart = GetCenterBehindPart();

	if (behindPart != nullptr)
	{
		float distanceX = center_BehindPart.x - center_CurrentPart.x;
		float distanceY = center_BehindPart.y - center_CurrentPart.y;

		if (abs(distanceX) > MoveMaxX)
		{
			transform->position.x = center_BehindPart.x - MoveMaxX * (distanceX / abs(distanceX));
		}

		if (abs(distanceY) > MoveMaxY)
		{
			transform->position.y = center_BehindPart.y - MoveMaxY * (distanceY / abs(distanceY));
		}
		center_CurrentPart = GetCenterCurrentPart();

		D3DXVECTOR2 center_Hand = GetCenterHand();
		if ((center_CurrentPart.x < center_Hand.x && center_CurrentPart.x < center_BehindPart.x) ||
			(center_CurrentPart.x > center_Hand.x && center_CurrentPart.x > center_BehindPart.x))
		{
			transform->position.x = center_BehindPart.x;
			center_CurrentPart = GetCenterCurrentPart();
		}

		if ((center_CurrentPart.y < center_Hand.y && center_CurrentPart.y < center_BehindPart.y) ||
			(center_CurrentPart.y > center_Hand.y && center_CurrentPart.y > center_BehindPart.y))
		{
			transform->position.y = center_BehindPart.y;
			center_CurrentPart = GetCenterCurrentPart();
		}

	}

	if (behindPart != nullptr && aheadPart != nullptr)
	{
		if (isFirstPart)
		{
			if ((isRightHand && center_AheadPart.x - center_CurrentPart.x > 0) || (!isRightHand && center_AheadPart.x - center_CurrentPart.x < 0) ||
				(abs(center_CurrentPart.x - center_AheadPart.x) > MoveMaxX || abs(center_CurrentPart.y - center_AheadPart.y) > MoveMaxY))
			{
				ReturnLimitPosition();
			}
			return;
		}
	}

	if (aheadPart != nullptr)
	{
		std::shared_ptr<HandPart> currentHandPart = std::dynamic_pointer_cast<HandPart>(aheadPart);
		if (currentHandPart != nullptr)
			currentHandPart->MoveFollowBehindHandPart();
	}

}

D3DXVECTOR2 HandPart::GetCenterCurrentPart()
{
	return { transform->position.x, transform->position.y };
}

D3DXVECTOR2 HandPart::GetCenterAheadPart()
{
	D3DXVECTOR2 center_AheadPart;
	if (aheadPart != nullptr)
	{
		center_AheadPart = { aheadPart->transform->position.x,aheadPart->transform->position.y };
	}

	if (std::dynamic_pointer_cast<BodyBoss>(aheadPart) != nullptr)
	{
		if (isRightHand)
		{
			center_AheadPart = { aheadPart->transform->position.x + 25.0f,aheadPart->transform->position.y + 8.0f };
		}
		else
		{
			center_AheadPart = { aheadPart->transform->position.x - 25.0f,aheadPart->transform->position.y + 8.0f };
		}
	}
	return center_AheadPart;
}

D3DXVECTOR2 HandPart::GetCenterBehindPart()
{
	D3DXVECTOR2 center_BehindPart;
	if (behindPart != nullptr)
	{
		center_BehindPart = { behindPart->transform->position.x,behindPart->transform->position.y };
	}

	if (std::dynamic_pointer_cast<RightHandBoss>(behindPart) != nullptr || std::dynamic_pointer_cast<LeftHandBoss>(behindPart) != nullptr)
	{
		center_BehindPart = { behindPart->transform->position.x,behindPart->transform->position.y + 8.0f };
	}
	return center_BehindPart;
}

D3DXVECTOR2 HandPart::GetCenterHand()
{
	D3DXVECTOR2 center_Hand;
	if (isRightHand)
	{
		center_Hand = { ownerObj->transform->position.x + 25.0f,ownerObj->transform->position.y + 8.0f };
	}
	else
	{
		center_Hand = { ownerObj->transform->position.x - 25.0f,ownerObj->transform->position.y + 8.0f };
	}
	return center_Hand;
}



