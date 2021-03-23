#include "d3dpch.h"
#include "Punji.h"

Punji::Punji(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Punji;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = true;
}
