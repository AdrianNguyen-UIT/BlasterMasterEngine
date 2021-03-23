#include "d3dpch.h"
#include "EnemyGuardian.h"

#include "Assets/Bullets/Enemy/EnemyGuardianBullet/EnemyGuardianBullet.h"
#include "Core/SceneManager/SceneManager.h"


EnemyGuardian::EnemyGuardian(float x, float y, float RunSpeed)
	: Enemy(x, y), runSpeed(RunSpeed)
{
	name = "Enemy Guardian";
}

void EnemyGuardian::CreateResources()
{
#pragma region animation
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 20;
	int spriteHeight = 32;
	KeyFrame keyFrame;
	RECT rect;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };


	std::shared_ptr<Animation> UpMove = std::make_shared<Animation>("Up Move");
	{
		UpMove->SetAnimationFPS(defaultFPS);
		for (int index = 0; index < 3; index++)
		{
			rect.left = 56 + (spriteWidth + 3) * index;
			rect.top = 780;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			UpMove->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(UpMove);
		animationController->SetDefaultAnimation(UpMove);
	}

	spriteWidth = 22;
	spriteHeight = 32;

	std::shared_ptr<Animation> DownMove = std::make_shared<Animation>("Down Move");
	{
		DownMove->SetAnimationFPS(defaultFPS);
		for (int index = 0; index < 3; index++)
		{
			rect.left = 132 + (spriteWidth + 3) * index;
			rect.top = 779;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			if (index == 2) rect.left -= 1;
			keyFrame.rect = rect;
			DownMove->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(DownMove);
	}

	std::shared_ptr<Animation> RightMove = std::make_shared<Animation>("Right Move");
	{
		RightMove->SetAnimationFPS(defaultFPS);
		for (int index = 0; index < 3; index++)
		{
			rect.left = 132 + (spriteWidth + 4) * index;
			rect.top = 812;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			RightMove->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(RightMove);
		animationController->SetDefaultAnimation(RightMove);
	}

	std::shared_ptr<Animation> LeftMove = std::make_shared<Animation>("Left Move");
	{
		LeftMove->SetAnimationFPS(defaultFPS);
		for (int index = 0; index < 3; index++)
		{
			rect.left = 48 + (spriteWidth + 4) * index;
			rect.top = 812;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			LeftMove->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(LeftMove);
	}
#pragma endregion

#pragma region transition
	std::shared_ptr<Parameter<bool>> isRightMove = std::make_shared<Parameter<bool>>("isRightMove");
	{
		animationController->AddBoolParameter(isRightMove);
	}
	std::shared_ptr<Parameter<bool>> isUpMove = std::make_shared<Parameter<bool>>("isUpMove");
	{
		animationController->AddBoolParameter(isUpMove);
	}
	std::shared_ptr<Parameter<bool>> isLeftMove = std::make_shared<Parameter<bool>>("isLeftMove");
	{
		animationController->AddBoolParameter(isLeftMove);
	}
	std::shared_ptr<Parameter<bool>> isDownMove = std::make_shared<Parameter<bool>>("isDownMove");
	{
		animationController->AddBoolParameter(isDownMove);
	}

	std::shared_ptr<TransitionCondition<bool>> isRightBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isRightBoolCond->SetParameter(isRightMove);
		isRightBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isLeftBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isLeftBoolCond->SetParameter(isLeftMove);
		isLeftBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isUpBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isUpBoolCond->SetParameter(isUpMove);
		isUpBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isDownBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isDownBoolCond->SetParameter(isDownMove);
		isDownBoolCond->SetValue(true);
	}

	// right to other
	std::shared_ptr<Transition> rightToLeft = std::make_shared<Transition>(
		animationController->GetAnimationIndex(RightMove),
		animationController->GetAnimationIndex(LeftMove));
	{
		rightToLeft->AddBoolTransitionCondition(isLeftBoolCond);
		animationController->AddTransition(rightToLeft);
	}

	std::shared_ptr<Transition> rightToUp = std::make_shared<Transition>(
		animationController->GetAnimationIndex(RightMove),
		animationController->GetAnimationIndex(UpMove));
	{
		rightToUp->AddBoolTransitionCondition(isUpBoolCond);
		animationController->AddTransition(rightToUp);
	}

	std::shared_ptr<Transition> rightToDown = std::make_shared<Transition>(
		animationController->GetAnimationIndex(RightMove),
		animationController->GetAnimationIndex(DownMove));
	{
		rightToDown->AddBoolTransitionCondition(isDownBoolCond);
		animationController->AddTransition(rightToDown);
	}

	// left to other
	std::shared_ptr<Transition> leftToRight = std::make_shared<Transition>(
		animationController->GetAnimationIndex(LeftMove),
		animationController->GetAnimationIndex(RightMove));
	{
		leftToRight->AddBoolTransitionCondition(isRightBoolCond);
		animationController->AddTransition(leftToRight);
	}

	std::shared_ptr<Transition> leftToUp = std::make_shared<Transition>(
		animationController->GetAnimationIndex(LeftMove),
		animationController->GetAnimationIndex(UpMove));
	{
		leftToUp->AddBoolTransitionCondition(isUpBoolCond);
		animationController->AddTransition(leftToUp);
	}

	std::shared_ptr<Transition> leftToDown = std::make_shared<Transition>(
		animationController->GetAnimationIndex(LeftMove),
		animationController->GetAnimationIndex(DownMove));
	{
		leftToDown->AddBoolTransitionCondition(isDownBoolCond);
		animationController->AddTransition(leftToDown);
	}

	// up to other
	std::shared_ptr<Transition> upToRight = std::make_shared<Transition>(
		animationController->GetAnimationIndex(UpMove),
		animationController->GetAnimationIndex(RightMove));
	{
		upToRight->AddBoolTransitionCondition(isRightBoolCond);
		animationController->AddTransition(upToRight);
	}

	std::shared_ptr<Transition> upToLeft = std::make_shared<Transition>(
		animationController->GetAnimationIndex(UpMove),
		animationController->GetAnimationIndex(LeftMove));
	{
		upToLeft->AddBoolTransitionCondition(isLeftBoolCond);
		animationController->AddTransition(upToLeft);
	}

	std::shared_ptr<Transition> upToDown = std::make_shared<Transition>(
		animationController->GetAnimationIndex(UpMove),
		animationController->GetAnimationIndex(DownMove));
	{
		upToDown->AddBoolTransitionCondition(isDownBoolCond);
		animationController->AddTransition(upToDown);
	}

	// down to other
	std::shared_ptr<Transition> downToRight = std::make_shared<Transition>(
		animationController->GetAnimationIndex(DownMove),
		animationController->GetAnimationIndex(RightMove));
	{
		downToRight->AddBoolTransitionCondition(isRightBoolCond);
		animationController->AddTransition(downToRight);
	}

	std::shared_ptr<Transition> downToLeft = std::make_shared<Transition>(
		animationController->GetAnimationIndex(DownMove),
		animationController->GetAnimationIndex(LeftMove));
	{
		downToLeft->AddBoolTransitionCondition(isLeftBoolCond);
		animationController->AddTransition(downToLeft);
	}

	std::shared_ptr<Transition> downToUp = std::make_shared<Transition>(
		animationController->GetAnimationIndex(DownMove),
		animationController->GetAnimationIndex(UpMove));
	{
		downToUp->AddBoolTransitionCondition(isUpBoolCond);
		animationController->AddTransition(downToUp);
	}
#pragma endregion
}

void EnemyGuardian::Start()
{
	Enemy::Start();

	runSpeed = 20.0f;
	isRightMove = false;
	isLeftMove = false;
	isUpMove = false;
	isDownMove = false;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 22.0f, 32.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_X, 0.0f };
	detectingPlayerZoneX = 100.0f;
	detectingPlayerZoneY = 100.0f;
	changeDirectionTime = 0.0f;
	shootTime = 0.0f;

	damage = 1;
}

void EnemyGuardian::Update()
{
	if (!IsInCameraBound()) {
		spriteRenderer->enable = false;
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		return;
	}
	else {
		spriteRenderer->enable = true;
		rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	}

	if (player == NULL)
		player = SceneManager::GetActiveScene()->FinObjectByName("OverworldJason");

	//DETECTING PLAYER
	if (abs((transform->position.x) - player->transform->position.x) <= detectingPlayerZoneX && abs((transform->position.y) - player->transform->position.y) <= detectingPlayerZoneY)
	{
		isNearPlayer = true;
	}
	else
	{
		isNearPlayer = false;
	}

	//MOVEMENT
	if (isNearPlayer == true)
	{
		if (Time::GetTime() - changeDirectionTime >= changeDirectionDelay)
		{
			float distanceX = abs(transform->position.x - player->transform->position.x);
			float distanceY = abs(transform->position.y - player->transform->position.y);
			if (distanceX > distanceY)
			{
				rigidbody->velocity.y = 0.0f;
				if (!(transform->position.x - player->transform->position.x < player->boxCollider->size.width / 2 &&
					transform->position.x - player->transform->position.x > -player->boxCollider->size.width / 2))
				{
					rigidbody->velocity.x = (transform->position.x < player->transform->position.x ? 1 : -1) * runSpeed * Time::GetFixedDeltaTime();
				}
				else rigidbody->velocity.x = 0.0f;
			}
			else
			{
				rigidbody->velocity.x = 0.0f;
				if (!(transform->position.y - player->transform->position.y < player->boxCollider->size.height / 2 &&
					transform->position.y - player->transform->position.y > -player->boxCollider->size.height / 2))
				{
					rigidbody->velocity.y = (transform->position.y < player->transform->position.y ? 1 : -1) * runSpeed * Time::GetFixedDeltaTime();
				}
				else rigidbody->velocity.y = 0.0f;
			}

			// set bool
			if (rigidbody->velocity.x > 0)
			{
				isRightMove = true;
				isLeftMove = false;
				direction = Direction::RIGHT;
			}
			else if (rigidbody->velocity.x < 0)
			{
				isRightMove = false;
				isLeftMove = true;
				direction = Direction::LEFT;
			}
			else
			{
				isRightMove = false;
				isLeftMove = false;
			}

			if (rigidbody->velocity.y > 0)
			{
				isUpMove = true;
				isDownMove = false;
				direction = Direction::UP;
			}
			else if (rigidbody->velocity.y < 0)
			{
				isUpMove = false;
				isDownMove = true;
				direction = Direction::DOWN;
			}
			else
			{
				isUpMove = false;
				isDownMove = false;
			}
			changeDirectionTime = Time::GetTime();
		}

		if (Time::GetTime() - shootTime >= delayShoot)
		{
			Shoot();
			shootTime = Time::GetTime();
		}
		shootTime += Time::GetFixedDeltaTime();
		changeDirectionTime += Time::GetFixedDeltaTime();
	}
	else
	{
		rigidbody->velocity = { 0.0f,0.0f };
	}
	SetAnimationParameter();

}


void EnemyGuardian::SetAnimationParameter()
{

	animationController->SetBool("isRightMove", isRightMove);

	animationController->SetBool("isUpMove", isUpMove);

	animationController->SetBool("isLeftMove", abs(isLeftMove));

	animationController->SetBool("isDownMove", abs(isDownMove));

}

void EnemyGuardian::Shoot()
{
	std::shared_ptr<Object2D> bullet = std::make_shared<EnemyGuardianBullet>(transform->position.x, transform->position.y, direction);
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, bullet->transform->position);
}