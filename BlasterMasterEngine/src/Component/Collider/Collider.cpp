#include "d3dpch.h"
#include "Collider.h"

BoxCollider2D::BoxCollider2D()
{
	isEnable = true;
	isTrigger = false;
	topLeft = { 0.0f, 0.0f };
	size.width = 0.0f;
	size.height = 0.0f;
	offset = { 0.0f, 0.0f };
}