#include "d3dpch.h"
#include "EnemyBulletHead.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"

EnemyBulletHead::EnemyBulletHead(float x, float y)
	: Enemy(x, y)
{
	name = "BulletHead";
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void EnemyBulletHead::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");
	int spriteWidthHor = 18;
	int spriteHeightHor = 17;
	int spriteWidthVer = 16;
	int spriteHeightVer = 19;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> bulletHeadFall = std::make_shared<Animation>("Bullet Head Fall");
	{
		bulletHeadFall->SetAnimationFPS(10);

		rect.left = 87;
		rect.top = 479;
		rect.right = 104;
		rect.bottom = 495;

		keyFrame.rect = rect;
		bulletHeadFall->AddKeyFrames(keyFrame);
		animationController->AddAnimation(bulletHeadFall);
		animationController->SetDefaultAnimation(bulletHeadFall);
	}

	std::shared_ptr<Animation> bulletHeadRunVertical = std::make_shared<Animation>("Bullet Head Run Vertical");
	{
		bulletHeadRunVertical->SetAnimationFPS(8);
		for (int index = 1; index < 3; index++)
		{
			rect.left = 105;
			rect.top = 441 + ((index - 1) * spriteHeightVer) + (index - 1);
			rect.right = rect.left + spriteWidthVer;
			rect.bottom = rect.top + spriteHeightVer;
			keyFrame.rect = rect;
			bulletHeadRunVertical->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(bulletHeadRunVertical);
	}

	std::shared_ptr<Animation> bulletHeadRunHorizontal = std::make_shared<Animation>("Bullet Head Run Horizontal");
	{
		bulletHeadRunHorizontal->SetAnimationFPS(8);
		for (int index = 1; index < 3; index++)
		{
			rect.left = 67 + ((index - 1) * spriteWidthHor) + (index-1);
			rect.top = 424;
			rect.right = rect.left + spriteWidthHor;
			rect.bottom = rect.top + spriteHeightHor;
			keyFrame.rect = rect;
			bulletHeadRunHorizontal->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(bulletHeadRunHorizontal);
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

	std::shared_ptr<Parameter<bool>> isClimbing = std::make_shared<Parameter<bool>>("isClimbing");
	{
		animationController->AddBoolParameter(isClimbing);
	}

	std::shared_ptr<TransitionCondition<bool>> isClimbingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isClimbingTrueBoolCond->SetParameter(isClimbing);
		isClimbingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isClimbingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isClimbingFalseBoolCond->SetParameter(isClimbing);
		isClimbingFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<Parameter<bool>> isOnLand = std::make_shared<Parameter<bool>>("isOnLand");
	{
		animationController->AddBoolParameter(isOnLand);
	}

	std::shared_ptr<TransitionCondition<bool>> isOnLandTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isOnLandTrueBoolCond->SetParameter(isOnLand);
		isOnLandTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isOnLandFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isOnLandFalseBoolCond->SetParameter(isOnLand);
		isOnLandFalseBoolCond->SetValue(false);
	}


	std::shared_ptr<Transition> runVerToFallTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(bulletHeadRunVertical),
		animationController->GetAnimationIndex(bulletHeadFall));
	{
		runVerToFallTrans->AddBoolTransitionCondition(isFallingTrueBoolCond);
		animationController->AddTransition(runVerToFallTrans);
	}

	std::shared_ptr<Transition> fallToRunVerTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(bulletHeadFall),
		animationController->GetAnimationIndex(bulletHeadRunVertical));
	{
		fallToRunVerTrans->AddBoolTransitionCondition(isClimbingTrueBoolCond);
		animationController->AddTransition(fallToRunVerTrans);
	}

	std::shared_ptr<Transition> fallToRunHorTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(bulletHeadFall),
		animationController->GetAnimationIndex(bulletHeadRunHorizontal));
	{
		fallToRunHorTrans->AddBoolTransitionCondition(isOnLandTrueBoolCond);
		animationController->AddTransition(fallToRunHorTrans);
	}
}

void EnemyBulletHead::Start()
{
	horizontalMove = 10.0f;
	verticalMove = 0.0f;
	time = 0.0f;
	isFacingRight = false;
	isFalling = true;
	isClimbing = false;
	isOnLand = false;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 16.0f, 17.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	damage = 0;
	detectRange = 150.0f;
}

void EnemyBulletHead::Update()
{
	if (!DetectPlayer())
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		spriteRenderer->enable = false;
		return;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	spriteRenderer->enable = true;

	player = SceneManager::GetActiveScene()->FinObjectByName("Sophia");
	//MOVEMENT AND ATTACK
	if (isFalling == false)
	{
		if (isClimbing == true)
		{
			rigidbody->gravityScale = 0.0f;
			horizontalMove = 0.0f;
			verticalMove = defaultVerticalMove;
			rigidbody->velocity.y = verticalMove * Time::GetFixedDeltaTime();
		}
		else if (isOnLand == true)
		{
			rigidbody->gravityScale = 1.0f;
			verticalMove = 0.0f;

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
	}
	else
	{
		rigidbody->gravityScale = 1.0f;
		verticalMove = 0.0f;
	}

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();


	//ANIMATION TRANS COND
	if (downCollision == 0 && rightCollision == 0 && leftCollision == 0)
	{
		isFalling = true;
		isClimbing = false;
		isOnLand = false;
	}
	else
	{
		isFalling = false;

		if ((downCollision == 0) && (rightCollision != 0 || leftCollision != 0))
		{
			isClimbing = true;
			isOnLand = false;
		}
		else if (downCollision != 0)
		{
			isClimbing = false;
			if (rightCollision == 0 && leftCollision == 0)
			{
				isOnLand = true;
			}
			else
				isOnLand = false;
		}
	}

	animationController->SetBool("isFalling", isFalling);
	animationController->SetBool("isClimbing", isClimbing);
	animationController->SetBool("isOnLand", isOnLand);


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

void EnemyBulletHead::OnCollisionStay(std::shared_ptr<Object2D> object)
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

void EnemyBulletHead::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void EnemyBulletHead::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}

void EnemyBulletHead::Die()
{
	SceneManager::DestroyObject(shared_from_this());
}