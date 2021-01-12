#include "d3dpch.h"
#include "EnemyWorm.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"

EnemyWorm::EnemyWorm(float x, float y)
	: Enemy(x, y)
{
	name = "Worm";
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void EnemyWorm::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");
	int spriteWidth = 18;
	int spriteHeight = 10;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
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
	detectRange = 150.0f;
	damage = 0;
}

void EnemyWorm::Update()
{
	if(!DetectPlayer())
	{
		spriteRenderer->enable = false;
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		return;
	}
	spriteRenderer->enable = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	//DETECTING SOPHIA(PLAYER) THE TANK 
	player = SceneManager::GetActiveScene()->FinObjectByName("Sophia");
	if (abs((transform->position.x) - player->transform->position.x) <= detectingPlayerZoneX && abs((transform->position.y) - player->transform->position.y) <= detectingPlayerZoneY)
	{
		isNearPlayer = true;
	}
	else
	{
		isNearPlayer = false;
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

void EnemyWorm::OnCollisionStay(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		std::shared_ptr<Sophia> sophia = std::dynamic_pointer_cast<Sophia>(object);
		if (sophia != NULL)
		{
			sophia->TakeDamage(damage);
		}

		std::shared_ptr<Jason> jason = std::dynamic_pointer_cast<Jason>(object);
		if (jason != NULL)
		{
			jason->TakeDamage(damage);
		}
	}
}

void EnemyWorm::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void EnemyWorm::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}