#include "d3dpch.h"
#include "SmallFireBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"

SmallFireBullet::SmallFireBullet(float x, float y, bool pIsFacingRight)
	: Object2D(x, y)
{
	name = "Small Fire Bullet";
	isFacingRight = pIsFacingRight;
	tag = Tag::PlayerBullet;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Projectile;
}

void SmallFireBullet::Start()
{
	runSpeed = 150.0f;
	boxCollider->size = { 4.0f, 4.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	damage = 1;
	transform->Scale(isFacingRight ? -WINDOW_CAMERA_SCALE_X : WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
}

void SmallFireBullet::Update()
{
	rigidbody->velocity.x = (isFacingRight ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime();
}

void SmallFireBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
	spriteRenderer->rect = {73, 38, 81, 46};
}

void SmallFireBullet::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
	Explode();
}

void SmallFireBullet::Explode()
{
	std::shared_ptr<Object2D> explosion = std::make_shared<NormalExplosion>(transform->position.x, transform->position.y);
	explosion->CreateResources();
	SceneManager::Instantiate(explosion, transform->position);
	SceneManager::DestroyObject(shared_from_this());
}
