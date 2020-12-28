#include "d3dpch.h"
#include "EnemySkullBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"

EnemySkullBullet::EnemySkullBullet(float x, float y, bool pIsAttackingFromRight)
	: Object2D(x, y)
{
	name = "EnemySkullBullet";
	tag = Tag::EnemyBullet;
	isAttackingFromRight = pIsAttackingFromRight;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void EnemySkullBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Bullet_Texture");

	int spriteWidth = 10;
	int spriteHeight = 10;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> bulletFly = std::make_shared<Animation>("Bullet Fly");
	{
		bulletFly->SetAnimationFPS(10);

		rect.left = 258;
		rect.top = 12;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;

		keyFrame.rect = rect;
		bulletFly->AddKeyFrames(keyFrame);
		animationController->AddAnimation(bulletFly);
		animationController->SetDefaultAnimation(bulletFly);
	}
}

void EnemySkullBullet::Start()
{
	rigidbody->mass = 3.0f;
	starting = true;
	isFacingRight = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 1.5f;
	rigidbody->bounciness = 0.7f;
	boxCollider->size = { 10.0f, 10.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
}

void EnemySkullBullet::Update()
{

	if (starting == true)
	{
		spawnBulletAt = Time::GetTime();
		if (isAttackingFromRight == true)
		{
			D3DXVECTOR2 force(-horizontalMoveAtStart, verticalMoveAtStart);
			rigidbody->AddForce(force);
		}
		else
		{
			D3DXVECTOR2 force(horizontalMoveAtStart, verticalMoveAtStart);
			rigidbody->AddForce(force);
		}
		starting = false;
	}

	if (Time::GetTime() - spawnBulletAt >= explosionDelayTime)
	{
		explosion = std::make_shared<NormalExplosion>(transform->position.x, transform->position.y);
		explosion->CreateResources();
		SceneManager::Instantiate(explosion, transform->position);
		SceneManager::DestroyObject(shared_from_this());
	}
}

void EnemySkullBullet::OnCollisionEnter(std::shared_ptr<Object2D> object)
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

		explosion = std::make_shared<NormalExplosion>(transform->position.x, transform->position.y);
		explosion->CreateResources();
		SceneManager::Instantiate(explosion, transform->position);
		SceneManager::DestroyObject(shared_from_this());
	}
}

void EnemySkullBullet::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void EnemySkullBullet::Flip()
{
}