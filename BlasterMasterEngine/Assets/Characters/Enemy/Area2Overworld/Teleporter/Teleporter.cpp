#include "d3dpch.h"
#include "Teleporter.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Assets/CameraBound.h"
#include "Assets/Particles/PlayerDeadExplosion.h"
#include "Assets/Bullets/Enemy/TeleporterBullet/TeleporterBullet.h"



Teleporter::Teleporter(float x, float y)
	: Enemy(x, y)
{
	name = "Teleporter";
}

void Teleporter::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 24;
	int spriteHeight = 32;

	KeyFrame keyFrame;
	RECT rect = { 0, 0, 0, 0 };
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> teleporterIdle = std::make_shared<Animation>("Teleporter Idle");
	{
		teleporterIdle->SetAnimationFPS(6);

		rect.left = 71;
		rect.top = 568;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		keyFrame.rect = rect;

		teleporterIdle->AddKeyFrames(keyFrame);

		animationController->AddAnimation(teleporterIdle);

		animationController->SetDefaultAnimation(teleporterIdle);
	}

	std::shared_ptr<Animation> teleporterTransform = std::make_shared<Animation>("Teleporter Transform");
	{
		teleporterTransform->SetAnimationFPS(12);

		for (size_t index = 0; index < 2; index++)
		{
			rect.left = 71 + (int)index * 27;
			rect.top = 568;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			teleporterTransform->AddKeyFrames(keyFrame);
		}

		animationController->AddAnimation(teleporterTransform);
	}

	std::shared_ptr<Animation> teleporterAttack = std::make_shared<Animation>("Teleporter Attack");
	{
		teleporterAttack->SetAnimationFPS(6);

		rect.left = 98;
		rect.top = 568;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		keyFrame.rect = rect;

		teleporterAttack->AddKeyFrames(keyFrame);

		animationController->AddAnimation(teleporterAttack);
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

	std::shared_ptr<Parameter<bool>> isDetect = std::make_shared<Parameter<bool>>("isDetect");
	{
		animationController->AddBoolParameter(isDetect);
	}

	std::shared_ptr<TransitionCondition<bool>> isDetectTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isDetectTrueBoolCond->SetParameter(isDetect);
		isDetectTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isDetectFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isDetectFalseBoolCond->SetParameter(isDetect);
		isDetectFalseBoolCond->SetValue(false);
	}

	//het gio nhay
	std::shared_ptr<Transition> attackingToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(teleporterAttack),
		animationController->GetAnimationIndex(teleporterIdle));
	{
		attackingToIdleTrans->AddBoolTransitionCondition(isAttackingFalseBoolCond);
		animationController->AddTransition(attackingToIdleTrans);
	}

	//thay player
	std::shared_ptr<Transition> idleToTransformTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(teleporterIdle),
		animationController->GetAnimationIndex(teleporterTransform));
	{
		idleToTransformTrans->AddBoolTransitionCondition(isDetectTrueBoolCond);
		animationController->AddTransition(idleToTransformTrans);
	}

	//duoi player
	std::shared_ptr<Transition> transformToAttackTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(teleporterTransform),
		animationController->GetAnimationIndex(teleporterAttack));
	{
		transformToAttackTrans->AddBoolTransitionCondition(isDetectTrueBoolCond);
		transformToAttackTrans->AddBoolTransitionCondition(isAttackingTrueBoolCond);
		animationController->AddTransition(transformToAttackTrans);
	}

}

void Teleporter::Start()
{
	Enemy::Start();
	srand(time(NULL));
	isTele = false;
	intervalAttack = 0;
	teleTime = 0.2f;
	teleCurrent = 0.0f;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 24.0f, 32.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	idleDelay = 1.0;
	currentIdleDelay = 0.0;
	transformAnimationDelay = 1.0f;
	attackStateDelay = 3.0f;
	attackDelay = 0.3f;
	detectZoneX = 5.0f;
	detectZoneY = 5.0f;
	transformCurrentTime = 0.0f;
	attackStateCurrentTime = 0.0f;
	attackCurrentTime = 0.0f;
	teleportDistance = 40.0f;
	transform->scale = { -3.0f, 3.0f, 3.0f };
	rigidbody->gravityScale = 0.0f;

	damage = 2;
}

void Teleporter::Update()
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

	if ((leftCollision != 0) || (rightCollision != 0))
	{
		rigidbody->velocity.x = 0;
	}
	if ((upCollision != 0) || (downCollision != 0))
	{
		rigidbody->velocity.y = 0;
	}
	AttackCheck();
	SetAnimationParameter();
}

void Teleporter::AttackCheck()
{
	if (player == NULL)
	{
		player = SceneManager::GetActiveScene()->FinObjectByName("OverworldJason");
	}
	else
	{
		if (animationController->GetCurrentAnimation()->GetName() == "Teleporter Idle")
		{
			currentIdleDelay += Time::GetDeltaTime();
			if (currentIdleDelay >= idleDelay)
			{
				isDetect = true;
				currentIdleDelay = 0.0f;
			}
		}
		if (animationController->GetCurrentAnimation()->GetName() == "Teleporter Transform")
		{
			transformCurrentTime += Time::GetDeltaTime();
			if (transformCurrentTime >= transformAnimationDelay)
			{
				isAttacking = true;
				transformCurrentTime = 0.0f;
			}
		}
		if (animationController->GetCurrentAnimation()->GetName() == "Teleporter Attack")
		{
			attackStateCurrentTime += Time::GetDeltaTime();
			if (attackStateCurrentTime >= attackStateDelay)
			{
				isAttacking = false;
				isDetect = false;
				attackStateCurrentTime = 0.0f;
			}
		}
		if (isAttacking == true)
		{
			attackCurrentTime += Time::GetDeltaTime();
			if (attackCurrentTime >= attackDelay)
			{
				Tele();
				isTele = true;
				attackCurrentTime = 0.0f;
			}
		}
		if (isTele == true)
		{
			teleCurrent += Time::GetDeltaTime();
			if (teleCurrent >= teleTime)
			{
				rigidbody->velocity.x = 0.0f;
				rigidbody->velocity.y = 0.0f;
				teleCurrent = 0.0f;
				isTele = false;
			}
		}
	}
}

void Teleporter::Attack()
{
	float dx = 0;
	float dy = 0;
	TranslateDirection(dx, dy);
	D3DXVECTOR3 location = { transform->position.x, transform->position.y - 18.0f, 0.0f };
	std::shared_ptr<Object2D> bullet = std::make_shared<TeleporterBullet>(dx, dy);
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, location);
}

void Teleporter::TranslateDirection(float& x, float& y)
{
	float playerPositionX = player->transform->position.x;
	float playerPositionY = player->transform->position.y;
	float telerporterPositionX = transform->position.x;
	float telerporterPositionY = transform->position.y;
	float vectorX = playerPositionX - telerporterPositionX;
	float vectorY = playerPositionY - telerporterPositionY;
	if ((vectorX != 0) && (vectorY != 0))
	{
		float degree = (180.0f * atan(abs(vectorX) / abs(vectorY)) / 3.1415f);
		if (vectorX > 0)
			x = sin(degree * 3.1415f / 180);
		else x = -sin(degree * 3.1415f / 180);
		if (vectorY > 0)
			y = cos(degree * 3.1415f / 180);
		else y = -cos(degree * 3.1415f / 180);
		/*std::string sString1 = "vectorX :" + std::to_string(vectorX) + "vectorY :" + std::to_string(vectorY);
		LOG_INFO(sString1);*/
		/*std::string sString2 = "x :" + std::to_string(x) + "y :" + std::to_string(y);
		LOG_INFO(sString2);*/
	}
	else
	{
		if (vectorX == 0)
		{
			x = 0;
			if (vectorY > 0)
				y = 1;
			else y = -1;
		}
		if (vectorY == 0)
		{
			y = 0;
			if (vectorX > 0)
				x = 1;
			else x = -1;
		}
	}
}

void Teleporter::Tele()
{
	intervalAttack++;
	if (intervalAttack == 2)
	{
		Attack();
		intervalAttack = 0;
	}
	int teleIdirection;
	Direction teleDirection;
	int i = 0;
	Direction* validDirection = new Direction[4];
	if (leftCollision == 0)
	{
		validDirection[i] = Direction::LEFT;
		i++;
	}
	/*else
		LOG_INFO("left is not valid");*/
	if (rightCollision == 0)
	{
		validDirection[i] = Direction::RIGHT;
		i++;
	}
	/*else
		LOG_INFO("right is not valid");*/
	if (downCollision == 0)
	{
		validDirection[i] = Direction::DOWN;
		i++;
	}
	/*else
		LOG_INFO("down is not valid");*/
	if (upCollision == 0)
	{
		validDirection[i] = Direction::UP;
		i++;
	}
	/*else
		LOG_INFO("up is not valid");*/
	if (i > 0)
	{
		teleIdirection = rand() % i;
		teleDirection = validDirection[teleIdirection];
		switch (teleDirection)
		{
		case Direction::UP:
			horizontalMove = 0.0f;
			verticalMove = 333.0f;
			break;
		case Direction::DOWN:
			horizontalMove = 0.0f;
			verticalMove = -333.0f;
			break;
		case Direction::RIGHT:
			horizontalMove = 333.0f;
			verticalMove = 0.0f;
			break;
		case Direction::LEFT:
			horizontalMove = -333.0f;
			verticalMove = 0.0f;
			break;
		}
	}
	delete[] validDirection;

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = verticalMove * Time::GetFixedDeltaTime();

}

void Teleporter::SetAnimationParameter()
{
	animationController->SetBool("isDetect", isDetect);
	animationController->SetBool("isAttacking", isAttacking);
}