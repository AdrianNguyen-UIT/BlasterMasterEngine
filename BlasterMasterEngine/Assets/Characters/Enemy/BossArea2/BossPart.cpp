#include "d3dpch.h"
#include "BossPart.h"
#include "Assets/Characters/Jason/OverworldJason.h"
#include "Assets/Characters/Enemy/BossArea2/BossArea2.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Core/SceneManager/SceneManager.h"

BossPart::BossPart(float x, float y)
	: Object2D(x, y)
{
	name = "Body Boss";
	tag = Tag::Boss;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void BossPart::CreateResources()
{
}

void BossPart::Start()
{
	damage = 1;
	rigidbody->mass = 1.0f;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->velocity = { 0.0f,0.0f };
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->isTrigger = true;
	transform->scale = ownerObj->transform->scale;
	transform->position = { ownerObj->transform->position.x + transform->position.x,
		ownerObj->transform->position.y + transform->position.y, 0.0f };
}

void BossPart::Update()
{
}

void BossPart::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		std::shared_ptr<OverworldJason> overworldJason = std::dynamic_pointer_cast<OverworldJason>(object);
		if (overworldJason != NULL)
		{
			overworldJason->TakeDamage(damage);
		}
	}
}

void BossPart::OnTriggerStay(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		std::shared_ptr<OverworldJason> overworldJason = std::dynamic_pointer_cast<OverworldJason>(object);
		if (overworldJason != NULL)
		{
			overworldJason->TakeDamage(damage);
		}
	}
}

void BossPart::Die()
{
	SceneManager::DestroyObject(shared_from_this());
}

void BossPart::TakeDamage(int damage)
{
	std::dynamic_pointer_cast<BossArea2>(ownerObj)->TakeDamage(damage);
}