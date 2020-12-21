#include "d3dpch.h"
#include "CheckPoint.h"
#include "Assets/CameraBound.h"

CheckPoint::CheckPoint(float x, float y)
	: Object2D(x, y)
{
	name = "CheckPoint";
	tag = Tag::CheckPoint;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Gate;
}

void CheckPoint::CreateResources()
{
	spriteRenderer->sprite = DeviceResources::LoadTexture(AREA2_MAP_PATH, 0);
}

void CheckPoint::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = true;
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f};
}