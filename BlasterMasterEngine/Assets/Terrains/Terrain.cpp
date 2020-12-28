#include "d3dpch.h"
#include "Terrain.h"

Terrain::Terrain(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Terrain;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();

	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = false;
}
