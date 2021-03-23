#include "d3dpch.h"
#include "RocketFireBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"
#include "Assets/Characters/Enemy/Area2EnemyList.h"

#include "Core/AudioMixer/AudioMixer.h"

RocketFireBullet::RocketFireBullet(float x, float y, bool pHorizontal, bool pIsFacingRight)
	: Bullet(x, y, pHorizontal, pIsFacingRight)
{
	name = "Rocket Fire Bullet";
	currentBulletX = x;
	currentBulletY = y;
	tag = Tag::PlayerBullet;
}

void RocketFireBullet::Start()
{
	rigidbody->velocity.x = 0.0f;
	rigidbody->velocity.y = 0.0f;
	runSpeed = 150.0f;
	horizontalRect = { 73, 30, 79, 34 };
	verticalRect = { 92, 29, 96, 35 };
	boxCollider->size = { 3.0f, 3.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	damage = 3;

	if (isFacingRight)
	{
		transform->Scale(-WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
		rocketSparkle->SetIsFacingRight(TRUE);
	}
	else
	{
		transform->Scale(WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
		rocketSparkle->SetIsFacingLeft(TRUE);
	}

	if (!horizontal)
	{
		rocketSparkle->SetIsFacingDown(TRUE);
		transform->Scale(WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
	}

	//? We get the list of current object rendered inside the camera
	std::list<std::shared_ptr<Object2D>> returnObjects;
	SceneManager::GetActiveScene()->RetrieveRenderableObjects(returnObjects);

	//@param to find the nearest enemy
	long nearestEnemyDistance = 999999;

	for (auto const& object : returnObjects)
	{
		if (object->tag == Tag::Enemy)
		{
			const long currentEnemyX = object->transform->position.x;
			const long currentEnemyY = object->transform->position.y;

			const long currentEnemyDistance = sqrt((pow(currentBulletX - currentEnemyX, 2) + pow(currentBulletY - currentEnemyY, 2) * 1.0));

			if (nearestEnemyDistance > currentEnemyDistance)
			{
				nearestEnemyDistance = currentEnemyDistance;
				nearestEnemy = object;
			}
		}
	}

	AudioMixer::PlayWaveFile("SOPHIA_ROCKET", FALSE);
}

void RocketFireBullet::Update()
{
	std::list<std::shared_ptr<Object2D>> returnObjects;
	SceneManager::GetActiveScene()->RetrieveRenderableObjects(returnObjects);

	std::list<std::shared_ptr<Object2D>>::iterator iteratorReturnObjects;

	if (nearestEnemy)
	{
		iteratorReturnObjects = std::find(returnObjects.begin(), returnObjects.end(), nearestEnemy);

		if (iteratorReturnObjects != returnObjects.end())
		{
			// spriteRenderer->rect = verticalRect;
			if (transform->position.x - nearestEnemy->transform->position.x > 1)
			{
				OnFollowEnemyX(TRUE);

			}
			else if (transform->position.x - nearestEnemy->transform->position.x < -1)
			{
				OnFollowEnemyX(FALSE);

			}
			else
			{

				if (transform->position.y - nearestEnemy->transform->position.y > 0)
				{
					OnFollowEnemyY(TRUE);
				}
				else if (transform->position.y - nearestEnemy->transform->position.y < 0)
				{
					OnFollowEnemyY(FALSE);

				}
			}
		}
		else
		{
			Explode();
		}
	}
	else
	{
		if (horizontal)
		{
			spriteRenderer->rect = horizontalRect;
			rigidbody->velocity.x = (isFacingRight ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime();
		}
		else
		{
			spriteRenderer->rect = verticalRect;
			rigidbody->velocity.y = runSpeed * Time::GetFixedDeltaTime();
		}

	}
}

void RocketFireBullet::OnFollowEnemyX(boolean Direction)
{
	if (Time::GetTime() - currentBulletTime >= changeDirectionDelayX)
	{
		switch (Direction)
		{
		case TRUE:
		{
			spriteRenderer->rect = horizontalRect;
			transform->Scale(WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
			currentBulletTime = Time::GetTime();
			rocketSparkle->SetIsFacingLeft(TRUE);
			isFacingRight = false;
			break;
		}
		case FALSE:
		{
			spriteRenderer->rect = horizontalRect;
			transform->Scale(-WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
			currentBulletTime = Time::GetTime();
			rocketSparkle->SetIsFacingRight(TRUE);
			isFacingRight = true;
			break;
		}
		default: return;
		}
	}
	rigidbody->velocity.x = (Direction ? -runSpeed : runSpeed) * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = 0;
}

void RocketFireBullet::OnFollowEnemyY(boolean Direction)
{
	if (Time::GetTime() - currentBulletTimeY >= changeDirectionDelayY)
	{
		switch (Direction)
		{
		case TRUE:
		{
			rocketSparkle->SetIsFacingTop(TRUE);
			spriteRenderer->rect = verticalRect;
			transform->Scale(WINDOW_CAMERA_SCALE_X, -WINDOW_CAMERA_SCALE_Y, 0.0f);
			currentBulletTimeY = Time::GetTime();
			break;
		}
		case FALSE:
		{
			rocketSparkle->SetIsFacingDown(TRUE);
			spriteRenderer->rect = verticalRect;
			transform->Scale(WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
			currentBulletTimeY = Time::GetTime();
			break;
		}
		default: return;
		}
	}
	rigidbody->velocity.x = 0;
	rigidbody->velocity.y = (Direction ? -runSpeed : runSpeed) * Time::GetFixedDeltaTime();
}

void RocketFireBullet::CreateResources()
{
	float scaleX = WINDOW_CAMERA_SCALE_X;
	float scaleY = WINDOW_CAMERA_SCALE_Y;

	{
		rocketSparkle = std::make_shared<RocketSparkle>(0, 0, false, isFacingRight, false, false);
		rocketSparkle->CreateResources();
		rocketSparkle->parentObject = shared_from_this();
		childObjects.emplace_back(rocketSparkle);
	}

	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
}