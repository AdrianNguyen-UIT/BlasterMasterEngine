#include "d3dpch.h"
#include "OverworldGate.h"

OverworldGate ::OverworldGate(int id, float x, float y)
	: Object2D(x, y), gateID(id)
{
	name = "OverworldGate";
	tag = Tag::Gate;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();

	layer = Layer::Gate;
}

void OverworldGate::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = true;
}
