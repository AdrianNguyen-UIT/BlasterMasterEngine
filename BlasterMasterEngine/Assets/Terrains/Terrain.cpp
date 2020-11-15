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

void Terrain::Start()
{

}

void Terrain::Update()
{

}

void Terrain::CreateResources()
{

}

void Terrain::OnCollisionEnter()
{
	//LOG_INFO("Terrain: Collide!");
}

void Terrain::OnTriggerEnter()
{
	//LOG_INFO("Terrain: Collide - Trigger!");
}