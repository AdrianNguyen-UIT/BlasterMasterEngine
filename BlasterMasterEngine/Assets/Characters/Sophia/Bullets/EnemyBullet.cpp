#include "d3dpch.h"
#include "EnemyBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalBulletExplosion.h"
EnemyBullet::EnemyBullet(float x, float y, bool pHorizontal, bool pIsFacingRight)
	: Object2D(x, y)
{
	name = "Normal Fire Bullet";
	horizontal = pHorizontal;
	isFacingRight = pIsFacingRight;
	tag = Tag::EnemyBullet;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void EnemyBullet::Start()
{
	runSpeed = 60.0f;
	horizontalRect = { 73, 20, 81, 28 };
	verticalRect = { 82, 20, 90, 28 };
	boxCollider->size = { 7.0f, 7.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
}

void EnemyBullet::Update()
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

	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}

void EnemyBullet::CreateResources()
{
	spriteRenderer->sprite = DeviceResources::LoadTexture(SOPHIA_JASON_TEXTURE_PATH, 0);
}

void EnemyBullet::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
}

void EnemyBullet::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
	explosion = std::make_shared<NormalBulletExplosion>(transform->position.x, transform->position.y);
	explosion->CreateResources();
	SceneManager::Instantiate(explosion, transform->position);
	SceneManager::DestroyObject(shared_from_this());
}