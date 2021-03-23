#include "d3dpch.h"
#include "HealthItem.h"
#include "Assets/Characters/PlayerHealth.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Core/AudioMixer/AudioMixer.h"

HeathPoint::HeathPoint(float x, float y)
	: Object2D(x, y)
{
	name = "Heath Point";

	tag = Tag::Item;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Projectile;
}

void HeathPoint::Start()
{
	horizontalRect = { 255, 109, 270, 124 };
	boxCollider->size = { 16.0f, 15.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	damage = 3;

	spriteRenderer->rect = horizontalRect;
	transform->Scale(WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
}

void HeathPoint::Update()
{
}

void HeathPoint::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Bullet_Texture");
}

void HeathPoint::OnTriggerStay(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		std::shared_ptr<Sophia> sophia = std::dynamic_pointer_cast<Sophia>(object);
		if (sophia != NULL)
		{
			IncreaseHP();
		}

		std::shared_ptr<Jason> jason = std::dynamic_pointer_cast<Jason>(object);
		if (jason != NULL)
		{
			IncreaseHP();
		}
	}
}

void HeathPoint::Die()
{
	AudioMixer::PlayWaveFile("ITEM_PICKING", FALSE);
	SceneManager::DestroyObject(shared_from_this());
}

void HeathPoint::IncreaseHP()
{
	int health = PlayerHealth::GetSophiaHealth();
	health += 1;
	if (health > PlayerHealth::GetMaxHealth())
	{
		health = PlayerHealth::GetMaxHealth();
	}
	PlayerHealth::SetJasonHealth(health);
	Die();
}
