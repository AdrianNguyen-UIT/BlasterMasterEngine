#include "d3dpch.h"
#include "NormalFireBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"
#include "Assets/Characters/Enemy/EnemyList.h"
NormalFireBullet::NormalFireBullet(float x, float y, bool pHorizontal, bool pIsFacingRight)
	: Object2D(x, y)
{
	name = "Normal Fire Bullet";
	horizontal = pHorizontal;
	isFacingRight = pIsFacingRight;
	tag = Tag::PlayerBullet;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Projectile;
}

void NormalFireBullet::Start()
{
	runSpeed = 150.0f;
	horizontalRect = {73, 20, 81, 28};
	verticalRect = {82, 20, 90, 28};
	boxCollider->size = { 7.0f, 7.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	damage = 3;
	transform->Scale(isFacingRight ? -WINDOW_CAMERA_SCALE_X : WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
}

void NormalFireBullet::Update()
{
	if (horizontal)
	{
		spriteRenderer->rect = horizontalRect;
		rigidbody->velocity.x = (isFacingRight ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime();
		rigidbody->velocity.y = 0.0f;
	}
	else
	{
		spriteRenderer->rect = verticalRect;
		rigidbody->velocity.x = 0.0f;
		rigidbody->velocity.y = runSpeed * Time::GetFixedDeltaTime();
	}
}

void NormalFireBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
}

void NormalFireBullet::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Enemy)
	{
		std::shared_ptr<Enemy> enemy = std::dynamic_pointer_cast<Enemy>(object);
		enemy->Die();
	}
	Explode();
}

void NormalFireBullet::Explode()
{
	std::shared_ptr<Object2D> explosion = std::make_shared<NormalExplosion>(transform->position.x, transform->position.y);
	explosion->CreateResources();
	SceneManager::Instantiate(explosion, transform->position);
	SceneManager::DestroyObject(shared_from_this());
}
