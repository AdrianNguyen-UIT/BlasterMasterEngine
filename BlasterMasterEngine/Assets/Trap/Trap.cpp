#include "d3dpch.h"
#include "Trap.h"

Trap::Trap(float x, float y)
	: Object2D(x, y)
{
	name = "Trap";
	tag = Tag::Trap;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
}

void Trap::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = true;
}