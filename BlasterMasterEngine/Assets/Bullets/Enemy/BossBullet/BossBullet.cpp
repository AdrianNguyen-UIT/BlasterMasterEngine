#include "d3dpch.h"
#include "BossBullet.h"
#include "Core/SceneManager/SceneManager.h"
BossBullet::BossBullet(float x, float y)
	: Bullet(x, y)
{
	name = "Boss Fire Bullet";
	tag = Tag::EnemyBullet;
}

void BossBullet::Start()
{
	runSpeed = 150.0f;
	boxCollider->size = { 9.0f, 9.0f };
	boxCollider->isTrigger = false;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	transform->Scale(WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
	spriteRenderer->rect = { 58,62,67,71 };

	std::shared_ptr<Object2D> player = SceneManager::GetActiveScene()->FinObjectByName("OverworldJason");
	D3DXVECTOR2 distanceToPlayer;
	distanceToPlayer.x = player->transform->position.x - transform->position.x;
	distanceToPlayer.y = player->transform->position.y - transform->position.y;

	int totalVelocity = sqrt(pow(distanceToPlayer.x, 2) + pow(distanceToPlayer.y, 2));
	if (totalVelocity == 0) totalVelocity = 1;
	rigidbody->velocity.x = distanceToPlayer.x * Time::GetFixedDeltaTime() * (runSpeed / totalVelocity);
	rigidbody->velocity.y = -abs(distanceToPlayer.y) * Time::GetFixedDeltaTime() * (runSpeed / totalVelocity);

	damage = 1;
}

void BossBullet::Update()
{
}

void BossBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Bullet_Texture");
}