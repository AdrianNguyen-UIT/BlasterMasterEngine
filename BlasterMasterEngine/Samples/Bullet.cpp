#include "d3dpch.h"
#include "Bullet.h"

Bullet::Bullet(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Player;
	spriteRenderer = GetComponent<SpriteRenderer>();
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	rigidbody->bodyType = Rigidbody::BodyType::Kinematic;
	//boxCollider->topLeft = { transform->position.x - boxCollider->size.width / 2, transform->position.y - boxCollider->size.height / 2 };
	boxCollider->isTrigger = false;
	boxCollider->size = { 25.0f, 30.0f };
	boxCollider->isTrigger = false;
}

void Bullet::Start()
{
	moveSpeed = 100.0f;
}

void Bullet::Update()
{
	rigidbody->velocity.x = moveSpeed * Time::GetDeltaTime();
}
void Bullet::CreateResources()
{
	int spriteWidth = 32;
	int spriteHeight = 32;
	int xOffset = 6;
	int yOffset = 6;

	RECT rect;
	rect.left = 0;
	rect.top = spriteHeight + yOffset;
	rect.right = rect.left + spriteWidth;
	rect.bottom = rect.top + spriteHeight;

	spriteRenderer->rect = rect;
}

void Bullet::OnCollisionEnter()
{
	//LOG_INFO("Bullet: Collide!");
}

void Bullet::OnTriggerEnter()
{
	//LOG_INFO("Bullet: Collide - Trigger!");
}
