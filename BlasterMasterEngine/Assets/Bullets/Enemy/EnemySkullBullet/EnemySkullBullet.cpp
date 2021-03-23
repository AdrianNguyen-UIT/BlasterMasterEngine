#include "d3dpch.h"
#include "EnemySkullBullet.h"

EnemySkullBullet::EnemySkullBullet(float x, float y, bool pIsAttackingFromRight)
	: Bullet(x, y), isAttackingFromRight(pIsAttackingFromRight)
{
	name = "EnemySkullBullet";
	tag = Tag::EnemyBullet;
	animationController = GetComponent<AnimationController>();
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
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 1.5f;
	rigidbody->bounciness = 0.7f;
	boxCollider->size = { 10.0f, 10.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	damage = 1;
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
		Explode();
	}
}