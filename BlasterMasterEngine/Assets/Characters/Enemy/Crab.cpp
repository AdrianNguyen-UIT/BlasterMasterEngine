#include "d3dpch.h"
#include "Crab.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Bullets/Enemy/CrabBullet.h"
Crab::Crab(float x, float y)
	: Object2D(x, y)
{
	name = "Crab ";
	tag = Tag::Enemy;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	animationController = GetComponent<AnimationController>();
	layer = Layer::Enemy;
}

void Crab::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 1.0f;
	boxCollider->size = { 18.0f, 15.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;

	iFrameColors[0] = { 0, 255, 0, 255 };
	iFrameColors[1] = { 255, 51, 0, 255 };
	iFrameColors[2] = { 255, 255, 255, 255 };
	iFrameColors[3] = { 255, 204, 255, 2255 };
	color = iFrameColors[2];

	isShooting = false;
	iFrame = false;
	shootingTime = 1.5f;
	minShootingTime = 1.5f;
	maxShootingTime = 4.0f;
	shootingInterval = 0.0f;
	iFrameTime = 0.0f;
	iFrameColorIndex = 0;
	start = true;

	hitPoint = 6;
	damage = 1;
}

void Crab::Update()
{
	if (start)
	{
		D3DXVECTOR2 force(20.0f, 0.0f);
		rigidbody->AddForce(force);
		start = false;
	}

	if (!isShooting)
	{
		if (shootingInterval >= shootingTime)
		{
			isShooting = true;
			shootingInterval = 0.0f;
			Shoot();
		}
		else
		{
			shootingInterval += Time::GetDeltaTime();
		}
	}
	else
	{
		if (shootingInterval >= 0.7f)
		{
			isShooting = false;
			shootingInterval = 0.0f;
		}
		else
		{
			shootingInterval += Time::GetDeltaTime();
		}
	}

	animationController->SetBool("isShooting", isShooting);

	float scalar = -1.0f * rigidbody->velocity.x / abs(rigidbody->velocity.x);
	transform->Scale(scalar * WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);

	DoIFrame();
	LOG_INFO("{0} {1}", transform->position.x, transform->position.y);
}

void Crab::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");
	KeyFrame keyFrame;
	RECT rect = { 0, 0, 0, 0 };
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };
	std::shared_ptr<Animation> crabIdle = std::make_shared<Animation>("Crab Idle");
	{
		crabIdle->SetAnimationFPS(6);

		rect.left = 84;
		rect.top = 407;
		rect.right = 102;
		rect.bottom = 422;

		keyFrame.rect = rect;
		crabIdle->AddKeyFrames(keyFrame);
		animationController->AddAnimation(crabIdle);
		animationController->SetDefaultAnimation(crabIdle);
	}

	std::shared_ptr<Animation> crabShoot = std::make_shared<Animation>("Crab Shoot");
	{
		crabShoot->SetAnimationFPS(6);

		rect.left = 104;
		rect.top = 406;
		rect.right = 122;
		rect.bottom = 422;

		keyFrame.rect = rect;
		crabShoot->AddKeyFrames(keyFrame);
		animationController->AddAnimation(crabShoot);
	}

	std::shared_ptr<Parameter<bool>> isShooting = std::make_shared<Parameter<bool>>("isShooting");
	{
		animationController->AddBoolParameter(isShooting);
	}

	std::shared_ptr<TransitionCondition<bool>> isShootingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isShootingFalseBoolCond->SetParameter(isShooting);
		isShootingFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<TransitionCondition<bool>> isShootingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isShootingTrueBoolCond->SetParameter(isShooting);
		isShootingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<Transition> idleToShootTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(crabIdle),
		animationController->GetAnimationIndex(crabShoot));
	{
		idleToShootTrans->AddBoolTransitionCondition(isShootingTrueBoolCond);
		animationController->AddTransition(idleToShootTrans);
	}

	std::shared_ptr<Transition> shootToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(crabShoot),
		animationController->GetAnimationIndex(crabIdle));
	{
		shootToIdleTrans->AddBoolTransitionCondition(isShootingFalseBoolCond);
		animationController->AddTransition(shootToIdleTrans);
	}
}

void Crab::OnCollisionEnter(std::shared_ptr<Object2D> object)
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

void Crab::TakeDamage(int p_Damage)
{
	hitPoint -= p_Damage;
	iFrame = true;

	if (hitPoint <= 0)
	{
		hitPoint = 0;
		Die();
	}
}

void Crab::DoIFrame()
{
	if (iFrame)
	{
		if (iFrameTime >= 0.45f)
		{
			iFrameTime = 0.0f;
			iFrame = false;
			iFrameColorIndex = 0;
			color = iFrameColors[2];
		}
		else
		{
			color = iFrameColors[iFrameColorIndex];
			++iFrameColorIndex;
			if (iFrameColorIndex > iFrameColors.size() - 1)
			{
				iFrameColorIndex = 0;
			}
			iFrameTime += Time::GetDeltaTime();
		}
	}
}

void Crab::GenerateRandomTimeToShoot()
{
	std::random_device rdev{};
	std::default_random_engine e{ rdev() };
	std::uniform_real_distribution<> dis(minShootingTime, maxShootingTime);
	shootingTime = dis(e);
}

void Crab::Shoot()
{
	float scalar = -1.0f * rigidbody->velocity.x / abs(rigidbody->velocity.x);
	std::shared_ptr<Object2D> bullet = std::make_shared<CrabBullet>(transform->position.x, transform->position.y, scalar);
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, bullet->transform->position);

	GenerateRandomTimeToShoot();
}

void Crab::Die()
{
	SceneManager::DestroyObject(shared_from_this());
}