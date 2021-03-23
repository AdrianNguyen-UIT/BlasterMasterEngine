#include "d3dpch.h"
#include "Bullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"
#include "Assets/Characters/Enemy/Enemy.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Assets/Characters/Jason/OverworldJason.h"
Bullet::Bullet(float x, float y, bool pHorizontal, bool pIsFacingRight)
	: Object2D(x, y), horizontal(pHorizontal), isFacingRight(pIsFacingRight)
{
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Projectile;
}

void Bullet::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Enemy)
	{
		std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(object);
		if (enemy != NULL)
			enemy->Die();
	}
	Explode();
}

void Bullet::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		/*std::shared_ptr<OverworldJason> overworldJason = std::dynamic_pointer_cast<OverworldJason>(object);
		if (overworldJason != NULL)
		{
			overworldJason->TakeDamage(damage);
		}

		std::shared_ptr<Sophia> sophia = std::dynamic_pointer_cast<Sophia>(object);
		if (sophia != NULL)
		{
			sophia->TakeDamage(damage);
		}

		std::shared_ptr<Jason> jason = std::dynamic_pointer_cast<Jason>(object);
		if (jason != NULL)
		{
			jason->TakeDamage(damage);
		}*/
	}

	Explode();
}

void Bullet::Explode()
{
	std::shared_ptr<Object2D> explosion = std::make_shared<NormalExplosion>(transform->position.x, transform->position.y);
	explosion->CreateResources();
	SceneManager::Instantiate(explosion, transform->position);
	SceneManager::DestroyObject(shared_from_this());
}