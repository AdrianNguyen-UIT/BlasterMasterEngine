#include "d3dpch.h"
#include "MainWorldGate.h"
#include "Assets/CameraBound.h"

MainWorldGate::MainWorldGate(float x, float y)
	: Object2D(x, y)
{
	name = "MainGate";
	tag = Tag::Gate;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	layer = Layer::Gate;
}

void MainWorldGate::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = false;
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f };
}