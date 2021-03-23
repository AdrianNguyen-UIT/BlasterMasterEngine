#include "d3dpch.h"
#include "Trap.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
Trap::Trap(float x, float y)
	: Object2D(x, y)
{
	name = "Trap ";
	tag = Tag::Trap;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
}

void Trap::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Kinematic;
	rigidbody->gravityScale = 0.0f;
	boxCollider->isTrigger = true;
	damage = 0;
}

void Trap::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player)
	{
		std::shared_ptr<Sophia> sophia = std::dynamic_pointer_cast<Sophia>(object);
		if (sophia != NULL)
		{
			sophia->TakeDamage(damage);
			return;
		}

		std::shared_ptr<Jason> jason = std::dynamic_pointer_cast<Jason>(object);
		if (jason != NULL)
		{
			jason->TakeDamage(damage);
			return;
		}
	}
}

void Trap::OnTriggerStay(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player)
	{
		std::shared_ptr<Sophia> sophia = std::dynamic_pointer_cast<Sophia>(object);
		if (sophia != NULL)
		{
			sophia->TakeDamage(damage);
			return;
		}

		std::shared_ptr<Jason> jason = std::dynamic_pointer_cast<Jason>(object);
		if (jason != NULL)
		{
			jason->TakeDamage(damage);
			return;
		}
	}
}