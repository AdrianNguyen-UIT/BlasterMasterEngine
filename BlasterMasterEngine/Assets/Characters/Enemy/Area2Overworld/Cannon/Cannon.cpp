#include "d3dpch.h"
#include "Cannon.h"
#include "Core/SceneManager/SceneManager.h"
#include <Assets/Bullets/Enemy/CanonBullet/CannonBullet.h>

Cannon::Cannon(float x, float y)
	: Enemy(x, y)
{
	name = "Cannon";
}

void Cannon::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 26;
	int spriteHeight = 26;

	KeyFrame keyFrame;
	RECT rect = { 0, 0, 0, 0 };
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> cannonIDle = std::make_shared<Animation>("Cannon Idle");
	{
		cannonIDle->SetAnimationFPS(6);

		rect.left = 96;
		rect.top = 603;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		keyFrame.rect = rect;

		cannonIDle->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cannonIDle);

		animationController->SetDefaultAnimation(cannonIDle);
	}

	std::shared_ptr<Animation> cannonVerticalAttack = std::make_shared<Animation>("Cannon Vertical Attack");
	{
		cannonVerticalAttack->SetAnimationFPS(4);

		rect.left = 41;
		rect.top = 607;
		spriteWidth = 26;
		spriteHeight = 22;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		keyFrame.rect = rect;

		cannonVerticalAttack->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cannonVerticalAttack);
	}

	std::shared_ptr<Animation> cannonHorizontalAttack = std::make_shared<Animation>("Cannon Horizontal Attack");
	{
		cannonHorizontalAttack->SetAnimationFPS(4);

		rect.left = 70;
		rect.top = 603;
		spriteWidth = 22;
		spriteHeight = 26;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		keyFrame.rect = rect;

		cannonHorizontalAttack->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cannonHorizontalAttack);
	}

	std::shared_ptr<Parameter<bool>> isWaitingAfterAttack = std::make_shared<Parameter<bool>>("isWaitingAfterAttack");
	{
		animationController->AddBoolParameter(isWaitingAfterAttack);
	}

	std::shared_ptr<TransitionCondition<bool>> isWaitingAfterAttackTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isWaitingAfterAttackTrueBoolCond->SetParameter(isWaitingAfterAttack);
		isWaitingAfterAttackTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isWaitingAfterAttackFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isWaitingAfterAttackFalseBoolCond->SetParameter(isWaitingAfterAttack);
		isWaitingAfterAttackFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<Parameter<bool>> isAttacking = std::make_shared<Parameter<bool>>("isAttacking");
	{
		animationController->AddBoolParameter(isAttacking);
	}

	std::shared_ptr<TransitionCondition<bool>> isAttackingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAttackingTrueBoolCond->SetParameter(isAttacking);
		isAttackingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isAttackingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAttackingFalseBoolCond->SetParameter(isAttacking);
		isAttackingFalseBoolCond->SetValue(false);
	}


	std::shared_ptr<Parameter<bool>> isVericalAttack = std::make_shared<Parameter<bool>>("isVerticalAttack");
	{
		animationController->AddBoolParameter(isVericalAttack);
	}

	std::shared_ptr<TransitionCondition<bool>> vericalAttackTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		vericalAttackTrueBoolCond->SetParameter(isVericalAttack);
		vericalAttackTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> vericalAttackFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		vericalAttackFalseBoolCond->SetParameter(isVericalAttack);
		vericalAttackFalseBoolCond->SetValue(false);
	}

	//dung yen xong ban doc
	std::shared_ptr<Transition> idleToVerticalShootTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cannonIDle),
		animationController->GetAnimationIndex(cannonVerticalAttack));
	{
		idleToVerticalShootTrans->AddBoolTransitionCondition(isAttackingTrueBoolCond);
		idleToVerticalShootTrans->AddBoolTransitionCondition(vericalAttackTrueBoolCond);
		animationController->AddTransition(idleToVerticalShootTrans);
	}
	//dung yen xong ban ngang
	std::shared_ptr<Transition> idleToHorizontalShootTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cannonIDle),
		animationController->GetAnimationIndex(cannonHorizontalAttack));
	{
		idleToHorizontalShootTrans->AddBoolTransitionCondition(isAttackingTrueBoolCond);
		idleToHorizontalShootTrans->AddBoolTransitionCondition(vericalAttackFalseBoolCond);
		animationController->AddTransition(idleToHorizontalShootTrans);
	}
	//ban ngang xong dung yen
	std::shared_ptr<Transition> horizontalShootToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cannonHorizontalAttack),
		animationController->GetAnimationIndex(cannonIDle));
	{
		horizontalShootToIdleTrans->AddBoolTransitionCondition(isWaitingAfterAttackTrueBoolCond);
		animationController->AddTransition(horizontalShootToIdleTrans);
	}
	//ban doc xong dung yen
	std::shared_ptr<Transition> vericalShootToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cannonVerticalAttack),
		animationController->GetAnimationIndex(cannonIDle));
	{
		vericalShootToIdleTrans->AddBoolTransitionCondition(isWaitingAfterAttackTrueBoolCond);
		animationController->AddTransition(vericalShootToIdleTrans);
	}
}

void Cannon::Start()
{
	Enemy::Start();

	rigidbody->bodyType = Rigidbody::BodyType::Kinematic;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 22.0f, 22.0f };
	boxCollider->offset = { -4.0f, -4.0f };
	isVerticalAttack = true;
	afterAttackDelayTime = 500.0f;
	attackingDelayTime = 200.0f;
	startAttackingAt = 0.0f;
	startWaitinAfterAttackgAt = 0.0;
	boxCollider->isTrigger = false;

	transform->scale = { -3.0f, 3.0f, 3.0f };
	rigidbody->gravityScale = 0.0f;

	damage = 0;
}

void Cannon::Update()
{
	if (!IsInCameraBound()) {
		spriteRenderer->enable = false;
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		return;
	}
	else {
		spriteRenderer->enable = true;
		rigidbody->bodyType = Rigidbody::BodyType::Kinematic;
	}

	AttackCheck();

	SetAnimationParameter();
}

void Cannon::SetAnimationParameter()
{
	animationController->SetBool("isWaitingAfterAttack", isWaitingAfterAttack);
	animationController->SetBool("isAttacking", isAttacking);
	animationController->SetBool("isVerticalAttack", isVerticalAttack);

}

void Cannon::AttackCheck()
{
	if (startWaitinAfterAttackgAt == 0.0f)
	{
		startWaitinAfterAttackgAt = Time::GetTime();
		isWaitingAfterAttack = true;
		isAttacking = false;
	}

	if (Time::GetTime() - startWaitinAfterAttackgAt >= afterAttackDelayTime)
	{
		if (startAttackingAt == 0.0f)
		{
			startAttackingAt = Time::GetTime();
			isAttacking = true;
			isWaitingAfterAttack = false;
			Attack();
		}

		if (Time::GetTime() - startAttackingAt >= attackingDelayTime)
		{
			startAttackingAt = 0.0f;
			isAttacking = false;
			startWaitinAfterAttackgAt = 0.0f;
			isWaitingAfterAttack = true;
		}
	}
}
void Cannon::Attack()
{
	D3DXVECTOR3 location_1;
	D3DXVECTOR3 location_2;
	if (isVerticalAttack == false)
	{
		isVerticalAttack = true;
		location_1 = { transform->position.x, transform->position.y + 15.0f, 0.0f };
		location_2 = { transform->position.x, transform->position.y - 18.0f, 0.0f };
		bullet_1 = std::make_shared<CannonBullet>(Direction::UP);
		bullet_2 = std::make_shared<CannonBullet>(Direction::DOWN);
	}
	else
	{
		isVerticalAttack = false;
		location_1 = { transform->position.x + 15.0f, transform->position.y, 0.0f };
		location_2 = { transform->position.x - 18.0f, transform->position.y, 0.0f };
		bullet_1 = std::make_shared<CannonBullet>(Direction::RIGHT);
		bullet_2 = std::make_shared<CannonBullet>(Direction::LEFT);
	}

	bullet_1->CreateResources();
	bullet_2->CreateResources();
	SceneManager::Instantiate(bullet_1, location_1);
	SceneManager::Instantiate(bullet_2, location_2);
}