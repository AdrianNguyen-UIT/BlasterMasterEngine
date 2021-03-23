#include "d3dpch.h"
#include "EnemyRedWalker.h"
#include "Assets/Bullets/Enemy/EnemyWalkerBullet/EnemyWalkerBullet.h"


EnemyRedWalker::EnemyRedWalker(float x, float y, float RunSpeed)
	: EnemyWalker(x, y, RunSpeed)
{
	name = "Enemy Red Walker";
}

void EnemyRedWalker::CreateResources()
{
#pragma region animation
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 18;
	int spriteHeight = 17;
	KeyFrame keyFrame;
	RECT rect;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };


	std::shared_ptr<Animation> IdleAnimation = std::make_shared<Animation>("Idle");
	{
		IdleAnimation->SetAnimationFPS(defaultFPS);

		rect.left = 84;
		rect.top = 1150;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		keyFrame.rect = rect;
		IdleAnimation->AddKeyFrames(keyFrame);

		animationController->AddAnimation(IdleAnimation);
		animationController->SetDefaultAnimation(IdleAnimation);
	}

	std::shared_ptr<Animation> AttackAnimation = std::make_shared<Animation>("Attack");
	{
		AttackAnimation->SetAnimationFPS(defaultFPS);
		for (int index = 0; index < 2; index++)
		{
			rect.left = 84 + (spriteWidth + 2) * index;
			rect.top = 1150;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			AttackAnimation->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(AttackAnimation);
	}

#pragma endregion

#pragma region transition
	std::shared_ptr<Parameter<bool>> isIdle = std::make_shared<Parameter<bool>>("isIdle");
	{
		animationController->AddBoolParameter(isIdle);
	}

	std::shared_ptr<TransitionCondition<bool>> isIdleBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isIdleBoolCond->SetParameter(isIdle);
		isIdleBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isAttackCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAttackCond->SetParameter(isIdle);
		isAttackCond->SetValue(false);
	}

	std::shared_ptr<Transition> idleToAttack = std::make_shared<Transition>(
		animationController->GetAnimationIndex(IdleAnimation),
		animationController->GetAnimationIndex(AttackAnimation));
	{
		idleToAttack->AddBoolTransitionCondition(isAttackCond);
		animationController->AddTransition(idleToAttack);
	}

	std::shared_ptr<Transition> attackToIdle = std::make_shared<Transition>(
		animationController->GetAnimationIndex(AttackAnimation),
		animationController->GetAnimationIndex(IdleAnimation));
	{
		attackToIdle->AddBoolTransitionCondition(isIdleBoolCond);
		animationController->AddTransition(attackToIdle);
	}
#pragma endregion
}

void EnemyRedWalker::Start()
{
	EnemyWalker::Start();
	shootTime = 0.0f;
	detectingPlayerZoneX = 100.0f;
	detectingPlayerZoneY = 100.0f;

	damage = 1;
}

void EnemyRedWalker::Shoot()
{
	std::shared_ptr<Object2D> bullet = std::make_shared<EnemyWalkerBullet>(transform->position.x, transform->position.y,
		direction, (direction == Direction::RIGHT ? false : true));
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, bullet->transform->position);
}
