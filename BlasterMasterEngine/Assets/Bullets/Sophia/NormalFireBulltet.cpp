#include "d3dpch.h"
#include "NormalFireBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"
#include "Assets/Characters/Enemy/Area2EnemyList.h"
#include "Core/AudioMixer/AudioMixer.h"
NormalFireBullet::NormalFireBullet(float x, float y, bool pHorizontal, bool pIsFacingRight)
	: Bullet(x, y, pHorizontal, pIsFacingRight)
{
	name = "Normal Fire Bullet";
	tag = Tag::PlayerBullet;
}

void NormalFireBullet::Start()
{
	runSpeed = 150.0f;
	horizontalRect = { 73, 20, 81, 28 };
	verticalRect = { 82, 20, 90, 28 };
	boxCollider->size = { 7.0f, 7.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	transform->Scale(isFacingRight ? -WINDOW_CAMERA_SCALE_X : WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
	AudioMixer::PlayWaveFile("NORMAL_BULLET_SHOOT", false);

	damage = 3;
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