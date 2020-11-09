#include "d3dpch.h"
#include "Dummy.h"

Dummy::Dummy(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Monster;
	//spriteRenderer = GetComponent<SpriteRenderer>();
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();

	rigidbody->bodyType = Rigidbody::BodyType::Static;
	//boxCollider->topLeft = { transform->position.x - boxCollider->size.width / 2, transform->position.y - boxCollider->size.height / 2 };
	boxCollider->isTrigger = false;
}

void Dummy::Start()
{
	
}

void Dummy::Update()
{
	//rigidbody->velocity.x = -40.0f * Time::GetDeltaTime();
}
void Dummy::CreateResources()
{
	/*int spriteWidth = 32;
	int spriteHeight = 32;
	int xOffset = 6;
	int yOffset = 6;

	RECT rect;
	rect.left = 0;
	rect.top = spriteHeight + yOffset;
	rect.right = rect.left + spriteWidth;
	rect.bottom = rect.top + spriteHeight;

	spriteRenderer->rect = rect;*/
}

void Dummy::OnCollisionEnter()
{
	//LOG_INFO("Dummy: Collide!");
}

void Dummy::OnTriggerEnter()
{
	//LOG_INFO("Dummy: Collide - Trigger!");
}