#include "d3dpch.h"
#include "EnemySkull.h"
#include "Assets/Bullets/Enemy/EnemySkullBullet/EnemySkullBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Core/AudioMixer/AudioMixer.h"
EnemySkull::EnemySkull(float x, float y)
	: Enemy(x, y)
{
	name = "Skull";
}

void EnemySkull::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 18;
	int spriteHeight = 21;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> skullFly = std::make_shared<Animation>("Skull Fly");
	{
		skullFly->SetAnimationFPS(10);

		rect.left = 42;
		rect.top = 527;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;

		keyFrame.rect = rect;
		skullFly->AddKeyFrames(keyFrame);
		animationController->AddAnimation(skullFly);
		animationController->SetDefaultAnimation(skullFly);
	}

	std::shared_ptr<Animation> skullAttack = std::make_shared<Animation>("Skull Attack");
	{
		skullAttack->SetAnimationFPS(10);

		rect.left = 62;
		rect.top = 527;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;

		keyFrame.rect = rect;
		skullAttack->AddKeyFrames(keyFrame);
		animationController->AddAnimation(skullAttack);
	}


	std::shared_ptr<Parameter<bool>> isAbovePlayer = std::make_shared<Parameter<bool>>("isAbovePlayer");
	{
		animationController->AddBoolParameter(isAbovePlayer);
	}

	std::shared_ptr<TransitionCondition<bool>> isAbovePlayerTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAbovePlayerTrueBoolCond->SetParameter(isAbovePlayer);
		isAbovePlayerTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isAbovePlayerFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAbovePlayerFalseBoolCond->SetParameter(isAbovePlayer);
		isAbovePlayerFalseBoolCond->SetValue(false);
	}


	std::shared_ptr<Transition> flyToAttackTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(skullFly),
		animationController->GetAnimationIndex(skullAttack));
	{
		flyToAttackTrans->AddBoolTransitionCondition(isAbovePlayerTrueBoolCond);
		animationController->AddTransition(flyToAttackTrans);
	}

	std::shared_ptr<Transition> attackToFlyTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(skullAttack),
		animationController->GetAnimationIndex(skullFly));
	{
		attackToFlyTrans->AddBoolTransitionCondition(isAbovePlayerFalseBoolCond);
		animationController->AddTransition(attackToFlyTrans);
	}
}

void EnemySkull::Start()
{
	Enemy::Start();
	horizontalMove = 2.0f;
	verticalMove = 0.0f;
	attackingAt = 0.0f;
	isFacingRight = false;
	isNearPlayer = false;
	isAbovePlayer = false;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 18.0f, 21.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };

	damage = 1;
	detectRange = 125.0f;
}

void EnemySkull::Update()
{
	//SPAWN RANGE
	if (!DetectPlayer())
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		spriteRenderer->enable = false;
		return;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	spriteRenderer->enable = true;

	std::shared_ptr<Object2D> player;
	//FINDING PLAYER
	if (jason == NULL)
	{
		player = sophia;
	}
	else
	{
		player = jason;
	}

	if (abs((transform->position.x) - player->transform->position.x) <= detectingPlayerZoneX && abs((transform->position.y) - player->transform->position.y) <= detectingPlayerZoneY)
	{
		isNearPlayer = true;
	}
	else
	{
		isNearPlayer = false;
	}


	//MOVEMENT AND ATTACK
	if (horizontalMove == 2.0f)
	{
		if (transform->position.x - player->transform->position.x > 0)
		{
			horizontalMove = -SpeedHor;
		}
		else
		{
			horizontalMove = SpeedHor;
		}
	}

	if (isNearPlayer == true)
	{
		if (horizontalMove > 0)
		{
			if (transform->position.x - player->transform->position.x >= 0 )
			{
				std::shared_ptr<Object2D> skullBullet = std::make_shared<EnemySkullBullet>(transform->position.x + 7.0f, transform->position.y - 5.0f, false);
				skullBullet->CreateResources();
				SceneManager::Instantiate(skullBullet, skullBullet->transform->position);
				attackingAt = Time::GetTime();
				isAbovePlayer = true;
				horizontalMove = 0.0f;
				verticalMove = SpeedVer;
				AudioMixer::PlayWaveFile("ENEMY_SKULL_ATTACK", false);
			}
		}
		else if (horizontalMove < 0)
		{
			if (transform->position.x - player->transform->position.x <= 0)
			{
				std::shared_ptr<Object2D> skullBullet = std::make_shared<EnemySkullBullet>(transform->position.x - 7.0f, transform->position.y - 5.0f, true);
				skullBullet->CreateResources();
				SceneManager::Instantiate(skullBullet, skullBullet->transform->position);
				attackingAt = Time::GetTime();
				isAbovePlayer = true;
				horizontalMove = 0.0f;
				verticalMove = SpeedVer;
				AudioMixer::PlayWaveFile("ENEMY_SKULL_ATTACK", false);
			}
		}
	}

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = verticalMove * Time::GetFixedDeltaTime();


	//ANIMATION TRANS COND
	animationController->SetBool("isAbovePlayer", isAbovePlayer);


	//FLIP COND
	if (isAbovePlayer == true)
	{
		if (Time::GetTime() - attackingAt >= attackingDelay)
		{
			Flip();
			isAbovePlayer = false;
		}
	}

	if (horizontalMove > 0 && !isFacingRight)
	{
		Flip();
	}
	else if (horizontalMove < 0 && isFacingRight)
	{
		Flip();
	}


	//DIE COND
	if (horizontalMove == 0.0f)
	{
		if (Time::GetTime() - attackingAt >= destructionDelay)
		{
			Die();
		}
	}
}