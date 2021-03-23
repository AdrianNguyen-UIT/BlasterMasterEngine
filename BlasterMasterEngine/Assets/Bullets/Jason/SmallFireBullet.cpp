#include "d3dpch.h"
#include "SmallFireBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"

SmallFireBullet::SmallFireBullet(float x, float y, bool pIsFacingRight)
	: Bullet(x, y, true, pIsFacingRight)
{
	name = "Small Fire Bullet";
	tag = Tag::PlayerBullet;
}

void SmallFireBullet::Start()
{
	runSpeed = 150.0f;
	boxCollider->size = { 4.0f, 4.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	transform->Scale(isFacingRight ? -WINDOW_CAMERA_SCALE_X : WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
	damage = 1;
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
