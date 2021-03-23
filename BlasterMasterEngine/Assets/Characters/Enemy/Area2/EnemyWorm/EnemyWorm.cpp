#include "d3dpch.h"
#include "EnemyWorm.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Core/AudioMixer/AudioMixer.h"
EnemyWorm::EnemyWorm(float x, float y, float fdetectRange)
	: Enemy(x, y)
{
	name = "Worm";
	detectRange = fdetectRange;
}

void EnemyWorm::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");
	int spriteWidth = 18;
	int spriteHeight = 10;
	KeyFrame keyFrame;
	RECT rect;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> wormIdle = std::make_shared<Animation>("Worm Idle");
	{
		wormIdle->SetAnimationFPS(10);

		rect.left = 46;
		rect.top = 412;
		rect.right = 63;
		rect.bottom = 422;

		keyFrame.rect = rect;
		wormIdle->AddKeyFrames(keyFrame);
		animationController->AddAnimation(wormIdle);
		animationController->SetDefaultAnimation(wormIdle);
		
	}

	std::shared_ptr<Animation> wormRun = std::make_shared<Animation>("Worm Run");
	{
		wormRun->SetAnimationFPS(3);
		for (int index = 1; index < 3; index++)
		{
			rect.left = 46 + ((index - 1) * spriteWidth);
			rect.top = 412;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			wormRun->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(wormRun);
	}

	std::shared_ptr<Parameter<bool>> isFalling = std::make_shared<Parameter<bool>>("isFalling");
	{
		animationController->AddBoolParameter(isFalling);
	}

	std::shared_ptr<TransitionCondition<bool>> isFallingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isFallingTrueBoolCond->SetParameter(isFalling);
		isFallingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isFallingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isFallingFalseBoolCond->SetParameter(isFalling);
		isFallingFalseBoolCond->SetValue(false);
	}


	std::shared_ptr<Transition> idleToRunTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wormIdle),
		animationController->GetAnimationIndex(wormRun));
	{
		idleToRunTrans->AddBoolTransitionCondition(isFallingFalseBoolCond);
		animationController->AddTransition(idleToRunTrans);
	}

	std::shared_ptr<Transition> runToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wormRun),
		animationController->GetAnimationIndex(wormIdle));
	{
		runToIdleTrans->AddBoolTransitionCondition(isFallingTrueBoolCond);
		animationController->AddTransition(runToIdleTrans);
	}
}

void EnemyWorm::Start()
{
	Enemy::Start();

	rigidbody->mass = 3.0f;
	horizontalMove = 0.0f;
	isFacingRight = false;
	isFalling = true;
	isNearPlayer = false;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 1.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 18.0f, 10.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	//detectRange = 200.0f;
	damage = 1;
}

void EnemyWorm::Update()
{
	//SPAWN RANGE
	if(!DetectPlayer())
	{
		spriteRenderer->enable = false;
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		return;
	}
	spriteRenderer->enable = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;

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

	if (Time::GetTime() - walkingTime >= audioWalkingDelay && allowWalkingAudio)
	{
		walkingTime = Time::GetTime();
		AudioMixer::PlayWaveFile("WORM_WALKING", FALSE);
		AudioMixer::SetVolume("WORM_WALKING", -2000);
	}

	if (abs((transform->position.x) - player->transform->position.x) <= detectingPlayerZoneX && abs((transform->position.y) - player->transform->position.y) <= detectingPlayerZoneY)
	{
		isNearPlayer = true;
		allowWalkingAudio = true;
	}
	else
	{
		isNearPlayer = false;
		allowWalkingAudio = false;
	}


	//MOVEMENT AND ATTACK
	if (isNearPlayer == true || downCollision != 0)
	{	
		if (transform->position.x - player->transform->position.x > 0)
		{
			if (Time::GetTime() - time >= reversingDelay)
			{
				horizontalMove = -defaultHorizontalMove;
				time = Time::GetTime();
			}
		}
		else
		{
			if (Time::GetTime() - time >= reversingDelay)
			{
				horizontalMove = defaultHorizontalMove;
				time = Time::GetTime();
			}
		}
	}

	if (isFalling == false)
	{
		if (leftCollision != 0 || rightCollision != 0)
		{
			D3DXVECTOR2 force(0, jumpForceY);
			rigidbody->AddForce(force);
		}
	}

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();


	//ANIMATION TRANS COND
	if (downCollision != 0)
	{
		isFalling = false;
	}
	else
	{
		isFalling = true;
	}
	animationController->SetBool("isFalling", isFalling);


	//FLIP COND
	if (horizontalMove > 0 && !isFacingRight)
	{
		Flip();
	}
	else if (horizontalMove < 0 && isFacingRight)
	{
		Flip();
	}
}