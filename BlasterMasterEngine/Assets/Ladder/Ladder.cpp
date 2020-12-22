#include "d3dpch.h"
#include "Ladder.h"

Ladder::Ladder(float x, float y)
	: Object2D(x, y)
{
	name = "Ladder ";
	tag = Tag::Ladder;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	layer = Layer::Ladder;
}

void Ladder::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = true;
}