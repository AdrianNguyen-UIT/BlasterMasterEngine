#pragma once

class BoxCollider2D
{
public:
	bool isEnable;
	bool isTrigger;
	D3DXVECTOR2 topLeft;
	Size size;

public:
	BoxCollider2D();
};