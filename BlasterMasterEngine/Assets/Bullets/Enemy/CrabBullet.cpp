#include "d3dpch.h"
#include "CrabBullet.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Assets/Particles/NormalExplosion.h"
#include "Core/SceneManager/SceneManager.h"

CrabBullet::CrabBullet(float x, float y, float scaleX)
	: Object2D(x, y)
{
	name = "Crab Bullet";
	tag = Tag::EnemyBullet;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	animationController = GetComponent<AnimationController>();
	layer = Layer::Projectile;
	transform->Scale( scaleX * 1.5f, abs(scaleX) * 1.5f, 0.0f);
}

void CrabBullet::Start()
{
	damage = 1;
	
	boxCollider->size = { 10.0f, 10.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 1.0f;
}

void CrabBullet::Update()
{
}

void CrabBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");
	KeyFrame keyFrame;
	RECT rect = { 0, 0, 0, 0 };
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };
	std::shared_ptr<Animation> crabBulletIdle = std::make_shared<Animation>("Crab Bullet Idle");
	{
		crabBulletIdle->SetAnimationFPS(6);

		rect.left = 51;
		rect.top = 515;
		rect.right = 61;
		rect.bottom = 525;

		keyFrame.rect = rect;
		crabBulletIdle->AddKeyFrames(keyFrame);

		rect.left = 51;
		rect.top = 1370;
		rect.right = 61;
		rect.bottom = 1380;
		keyFrame.rect = rect;
		crabBulletIdle->AddKeyFrames(keyFrame);

		animationController->AddAnimation(crabBulletIdle);
		animationController->SetDefaultAnimation(crabBulletIdle);
	}
}

void CrabBullet::OnTriggerEnter(std::shared_ptr<Object2D> object)
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

	std::shared_ptr<Object2D> explosion = std::make_shared<NormalExplosion>(transform->position.x, transform->position.y);
	explosion->CreateResources();
	SceneManager::Instantiate(explosion, transform->position);
	SceneManager::DestroyObject(shared_from_this());
}
