#include "d3dpch.h"
#include "EnemyLegRobot.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"

EnemyLegRobot::EnemyLegRobot(float x, float y, bool bGoRightFirst, float fHorizontalMoveRange, float fDetectingPlayerZoneX, float fDetectingPlayerZoneY)
	: Enemy(x, y)
{
	name = "LegRobot";
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	horizontalMoveRange = fHorizontalMoveRange;
	goRightFirst = bGoRightFirst;
	detectingPlayerZoneX = fDetectingPlayerZoneX;
	detectingPlayerZoneY = fDetectingPlayerZoneY;
}

void EnemyLegRobot::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 17;
	int spriteHeight = 26;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> legRobotWalk = std::make_shared<Animation>("Leg Robot Walk");
	{
		legRobotWalk->SetAnimationFPS(3);

		for (int index = 1; index < 5; index++)
		{
			if (index == 4)
			{
				rect.left = 87;
				rect.top = 499;
				rect.right = rect.left + spriteWidth;
				rect.bottom = rect.top + spriteHeight;
			}
			else
			{
				rect.left = 69 + ((index - 1) * spriteWidth) + (index - 1);
				rect.top = 499;
				rect.right = rect.left + spriteWidth;
				rect.bottom = rect.top + spriteHeight;
				keyFrame.rect = rect;
			}
			
			legRobotWalk->AddKeyFrames(keyFrame);
		}

		keyFrame.rect = rect;
		legRobotWalk->AddKeyFrames(keyFrame);
		animationController->AddAnimation(legRobotWalk);
	}

	std::shared_ptr<Animation> legRobotOnAir = std::make_shared<Animation>("Leg Robot On Air");
	{
		legRobotOnAir->SetAnimationFPS(10);

		rect.left = 69;
		rect.top = 499;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;

		keyFrame.rect = rect;
		legRobotOnAir->AddKeyFrames(keyFrame);
		animationController->AddAnimation(legRobotOnAir);
		animationController->SetDefaultAnimation(legRobotOnAir);
	}

	std::shared_ptr<Animation> legRobotStandingStill = std::make_shared<Animation>("Leg Robot Standing Still");
	{
		legRobotStandingStill->SetAnimationFPS(10);

		rect.left = 87;
		rect.top = 499;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;

		keyFrame.rect = rect;
		legRobotStandingStill->AddKeyFrames(keyFrame);
		animationController->AddAnimation(legRobotStandingStill);
	}


	std::shared_ptr<Parameter<bool>> isWaiting = std::make_shared<Parameter<bool>>("isWaiting");
	{
		animationController->AddBoolParameter(isWaiting);
	}

	std::shared_ptr<TransitionCondition<bool>> isWaitingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isWaitingTrueBoolCond->SetParameter(isWaiting);
		isWaitingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isWaitingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isWaitingFalseBoolCond->SetParameter(isWaiting);
		isWaitingFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<Parameter<bool>> isNearPlayer = std::make_shared<Parameter<bool>>("isNearPlayer");
	{
		animationController->AddBoolParameter(isNearPlayer);
	}

	std::shared_ptr<TransitionCondition<bool>> isNearPlayerTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isNearPlayerTrueBoolCond->SetParameter(isNearPlayer);
		isNearPlayerTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isNearPlayerFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isNearPlayerFalseBoolCond->SetParameter(isNearPlayer);
		isNearPlayerFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<Parameter<bool>> isOnAir = std::make_shared<Parameter<bool>>("isOnAir");
	{
		animationController->AddBoolParameter(isOnAir);
	}

	std::shared_ptr<TransitionCondition<bool>> isOnAirTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isOnAirTrueBoolCond->SetParameter(isOnAir);
		isOnAirTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isOnAirFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isOnAirFalseBoolCond->SetParameter(isOnAir);
		isOnAirFalseBoolCond->SetValue(false);
	}


	std::shared_ptr<Transition> jumpToStandTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(legRobotOnAir),
		animationController->GetAnimationIndex(legRobotStandingStill));
	{
		jumpToStandTrans->AddBoolTransitionCondition(isOnAirFalseBoolCond);
		animationController->AddTransition(jumpToStandTrans);
	}

	std::shared_ptr<Transition> standToJumpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(legRobotStandingStill),
		animationController->GetAnimationIndex(legRobotOnAir));
	{
		standToJumpTrans->AddBoolTransitionCondition(isNearPlayerTrueBoolCond);
		standToJumpTrans->AddBoolTransitionCondition(isOnAirTrueBoolCond);
		animationController->AddTransition(standToJumpTrans);
	}

	std::shared_ptr<Transition> standToWalkTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(legRobotStandingStill),
		animationController->GetAnimationIndex(legRobotWalk));
	{
		standToWalkTrans->AddBoolTransitionCondition(isNearPlayerFalseBoolCond);
		standToWalkTrans->AddBoolTransitionCondition(isOnAirFalseBoolCond);
		animationController->AddTransition(standToWalkTrans);
	}

	std::shared_ptr<Transition> walkToStandTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(legRobotWalk),
		animationController->GetAnimationIndex(legRobotStandingStill));
	{
		walkToStandTrans->AddBoolTransitionCondition(isNearPlayerTrueBoolCond);
		walkToStandTrans->AddBoolTransitionCondition(isOnAirFalseBoolCond);
		walkToStandTrans->AddBoolTransitionCondition(isWaitingTrueBoolCond);
		animationController->AddTransition(walkToStandTrans);
	}
}

void EnemyLegRobot::Start()
{
	rigidbody->mass = 3.0f;
	horizontalMove = 0.0f;
	beginningX = 0.0f;
	startJumpingAt = 0.0f;
	isFacingRight = false;
	isNearPlayer = false;
	isWaiting = false;
	isOnAir = true;
	startWalking = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 2.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 17.0f, 26.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	damage = 0;
	detectRange = 150.0f;
}

void EnemyLegRobot::Update()
{
	if (!DetectPlayer())
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		spriteRenderer->enable = false;
		return;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	spriteRenderer->enable = true;

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
	if (downCollision != 0)
	{
		if (isNearPlayer == true)
		{
			beginningX = 0.0f;
			horizontalMove = 0.0f;

			if (startJumpingAt == 0.0f)
			{
				startJumpingAt = Time::GetTime();
				isWaiting = true;
				if (startWalking == false)
				{
					if ((isFacingRight == true && (transform->position.x > player->transform->position.x)) ||
						(isFacingRight == false && (transform->position.x < player->transform->position.x)))
					{
						Flip();
					}
					startWalking = true;
				}
			}

			if (isWaiting == true)
			{
				rigidbody->velocity.x = 0.0f;
			}

			if (Time::GetTime() - startJumpingAt >= jumpingDelay)
			{
				startJumpingAt = 0.0f;
				isWaiting = false;
				if (transform->position.x - player->transform->position.x > 0)
				{
					D3DXVECTOR2 force(-jumpForceX, jumpForceY);
					rigidbody->AddForce(force);
				}
				else
				{
					D3DXVECTOR2 force(jumpForceX, jumpForceY);
					rigidbody->AddForce(force);
				}
			}
		}
		else
		{
			startJumpingAt = 0.0f;
			isWaiting = false;

			if (beginningX == 0.0f)
			{
				beginningX = transform->position.x;
			}
			else if (leftCollision != 0)
			{
				beginningX = transform->position.x + horizontalMoveRange;
			}
			else if (rightCollision != 0)
			{
				beginningX = transform->position.x - horizontalMoveRange;
			}

			if (horizontalMove == 0.0f)
			{
				if (startWalking == true)
				{
					horizontalMove = (goRightFirst ? defaultHorizontalMove : -defaultHorizontalMove);
					startWalking = false;
				}
			}

			if (transform->position.x >= (beginningX + horizontalMoveRange) || transform->position.x <= (beginningX - horizontalMoveRange))
			{
				horizontalMove = -horizontalMove;
			}
			rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();
		}
	}


	//ANIMATION TRANS COND
	if (downCollision != 0)
	{
		isOnAir = false;
	}
	else
	{
		isOnAir = true;
	}

	animationController->SetBool("isNearPlayer", isNearPlayer);
	animationController->SetBool("isOnAir", isOnAir);
	animationController->SetBool("isWaiting", isWaiting);


	//FLIP COND
	if (rigidbody->velocity.x > 0 && !isFacingRight)
	{
		Flip();
	}
	else if (rigidbody->velocity.x < 0 && isFacingRight)
	{
		Flip();
	}
}

void EnemyLegRobot::OnCollisionStay(std::shared_ptr<Object2D> object)
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

void EnemyLegRobot::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void EnemyLegRobot::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}