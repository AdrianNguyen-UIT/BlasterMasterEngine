#include "d3dpch.h"
#include "IndoorHorizontalCheckpoint.h"
#include "Assets/CameraBound.h"

IndoorHorizontalCheckpoint::IndoorHorizontalCheckpoint(float x, float y)
	: Object2D(x, y)
{
	name = "IndoorHorizontalCheckpoint";
	tag = Tag::CheckPoint;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	layer = Layer::Gate;
}

void IndoorHorizontalCheckpoint::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = false;
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f };
}