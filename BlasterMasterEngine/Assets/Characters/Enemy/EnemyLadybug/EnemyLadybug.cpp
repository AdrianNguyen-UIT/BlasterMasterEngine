#include "d3dpch.h"
#include "EnemyLadybug.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"


EnemyLadybug::EnemyLadybug(float x, float y, float xMove)
	: Enemy(x, y)
{
	name = "Ladybug";
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	horizontalMove = xMove;
}

void EnemyLadybug::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 18;
	int spriteHeight = 18;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };


	std::shared_ptr<Animation> ladybugTurningRight = std::make_shared<Animation>("Ladybug Turning Right");
	{
		ladybugTurningRight->SetIsLooping(false);
		ladybugTurningRight->SetAnimationFPS(defaultFPS);
		for (int index = 1; index < 5; index++)
		{
			rect.left = 98 + ((index - 1) * spriteWidth) + (index - 1) * 2;
			rect.top = 387;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			ladybugTurningRight->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(ladybugTurningRight);
		animationController->SetDefaultAnimation(ladybugTurningRight);
	}

	std::shared_ptr<Animation> ladybugTurningLeft = std::make_shared<Animation>("Ladybug Turning Left");
	{
		ladybugTurningLeft->SetIsLooping(false);
		ladybugTurningLeft->SetAnimationFPS(defaultFPS);
		for (int index = 1; index < 5; index++)
		{
			rect.left = 138 - ((index - 1) * spriteWidth) - (index - 1) * 2;
			rect.top = 387;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			ladybugTurningLeft->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(ladybugTurningLeft);
	}


	std::shared_ptr<Parameter<bool>> isRightCollision = std::make_shared<Parameter<bool>>("isRightCollision");
	{
		animationController->AddBoolParameter(isRightCollision);
	}

	std::shared_ptr<TransitionCondition<bool>> isRightCollisionTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isRightCollisionTrueBoolCond->SetParameter(isRightCollision);
		isRightCollisionTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isRightCollisionFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isRightCollisionFalseBoolCond->SetParameter(isRightCollision);
		isRightCollisionFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<Parameter<bool>> isLeftCollision = std::make_shared<Parameter<bool>>("isLeftCollision");
	{
		animationController->AddBoolParameter(isLeftCollision);
	}

	std::shared_ptr<TransitionCondition<bool>> isLeftCollisionTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isLeftCollisionTrueBoolCond->SetParameter(isLeftCollision);
		isLeftCollisionTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isLeftCollisionFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isLeftCollisionFalseBoolCond->SetParameter(isLeftCollision);
		isLeftCollisionFalseBoolCond->SetValue(false);
	}


	std::shared_ptr<Transition>turningRightToTurningLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(ladybugTurningRight),
		animationController->GetAnimationIndex(ladybugTurningLeft));
	{
		turningRightToTurningLeftTrans->AddBoolTransitionCondition(isRightCollisionTrueBoolCond);
		animationController->AddTransition(turningRightToTurningLeftTrans);
	}


	std::shared_ptr<Transition> turningLeftToTurningRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(ladybugTurningLeft),
		animationController->GetAnimationIndex(ladybugTurningRight));
	{
		turningLeftToTurningRightTrans->AddBoolTransitionCondition(isLeftCollisionTrueBoolCond);
		animationController->AddTransition(turningLeftToTurningRightTrans);
	}
}

void EnemyLadybug::Start()
{
	isFacingRight = true;
	isRightCollision = false;
	isLeftCollision = false;
	starting = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 18.0f, 18.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	damage = 0;
	detectRange = 150.0f;
}

void EnemyLadybug::Update()
{
	if (!DetectPlayer())
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		spriteRenderer->enable = false;
		return;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	spriteRenderer->enable = true;

	//MOVEMENT
	if (starting == true)
	{
		if (horizontalMove > 0)
		{
			isLeftCollision = true;
			isRightCollision = false;
		}
		else
		{
			isLeftCollision = false;
			isRightCollision = true;
		}
		starting = false;
	}
	else
	{
		if (rightCollision != 0)
		{
			isRightCollision = true;
			horizontalMove = -horizontalMove;
		}
		else if (leftCollision != 0)
		{
			isLeftCollision = true;
			horizontalMove = -horizontalMove;
		}
		else
		{
			isLeftCollision = false;
			isRightCollision = false;
		}
	}

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();


	//ANIMATION TRANS COND
	animationController->SetBool("isRightCollision", isRightCollision);
	animationController->SetBool("isLeftCollision", isLeftCollision);
}

void EnemyLadybug::OnCollisionStay(std::shared_ptr<Object2D> object)
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

void EnemyLadybug::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void EnemyLadybug::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}