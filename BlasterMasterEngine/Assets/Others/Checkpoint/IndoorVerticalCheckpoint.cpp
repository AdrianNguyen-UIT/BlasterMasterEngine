#include "d3dpch.h"
#include "IndoorVerticalCheckpoint.h"
#include "Assets/CameraBound.h"

IndoorVerticalCheckpoint::IndoorVerticalCheckpoint(float x, float y)
	: Object2D(x, y)
{
	name = "IndoorVerticalCheckpoint";
	tag = Tag::CheckPoint;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	layer = Layer::Gate;
}

void IndoorVerticalCheckpoint::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = false;
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f };
}