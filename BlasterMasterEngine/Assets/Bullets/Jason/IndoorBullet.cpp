#include "d3dpch.h"
#include "IndoorBullet.h"
#include "Core/SceneManager/SceneManager.h"
#include <Assets/Characters/Enemy/BossArea2/BossPart.h>

IndoorBullet::IndoorBullet(Direction pDirection, float x, float y)
	: Bullet(x, y), direction(pDirection)
{
	name = "Normal Fire Bullet";
	tag = Tag::PlayerBullet;
}

void IndoorBullet::Start()
{
	runSpeed = 150.0f;
	horizontalRect = { 73, 20, 81, 28 };
	verticalRect = { 82, 20, 90, 28 };
	boxCollider->size = { 7.0f, 7.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	transform->Scale(isFacingRight ? -WINDOW_CAMERA_SCALE_X : WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);

	damage = 3;
}

void IndoorBullet::Update()
{
	switch (direction)
	{
	case Direction::UP:
		spriteRenderer->rect = verticalRect;
		rigidbody->velocity.x = 0.0f;
		rigidbody->velocity.y = 1.0f * runSpeed * Time::GetFixedDeltaTime();
		transform->Scale(3.0f, -3.0f, 0.0f);
		break;
	case Direction::DOWN:
		spriteRenderer->rect = verticalRect;
		rigidbody->velocity.x = 0.0f;
		rigidbody->velocity.y = -1.0f * runSpeed * Time::GetFixedDeltaTime();
		transform->Scale(3.0f, 3.0f, 0.0f);
		break;
	case Direction::RIGHT:
		spriteRenderer->rect = horizontalRect;
		rigidbody->velocity.x = 1.0f * runSpeed * Time::GetFixedDeltaTime();
		rigidbody->velocity.y = 0.0;
		transform->Scale(-3.0f, 3.0f, 0.0f);
		break;
	case Direction::LEFT:
		spriteRenderer->rect = horizontalRect;
		rigidbody->velocity.x = -1.0f * runSpeed * Time::GetFixedDeltaTime();
		rigidbody->velocity.y = 0.0;
		transform->Scale(3.0f, 3.0f, 0.0f);
		break;
	}
}

void IndoorBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
}

void IndoorBullet::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Boss)
	{
		std::shared_ptr<BossPart> bossPart = std::dynamic_pointer_cast<BossPart>(object);
		if (bossPart != NULL)
		{
			bossPart->TakeDamage(damage);
		}
	}

	Bullet::OnTriggerEnter(object);

}
