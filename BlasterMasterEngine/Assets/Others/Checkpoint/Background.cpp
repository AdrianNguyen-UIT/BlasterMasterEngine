#include "d3dpch.h"
#include "Background.h"
#include "Assets/CameraBound.h"

Background::Background(float x, float y)
	: Object2D(x, y)
{
	name = "Background";
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void Background::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Area2_Overworld_Texture");
}

void Background::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = true;
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f };
}