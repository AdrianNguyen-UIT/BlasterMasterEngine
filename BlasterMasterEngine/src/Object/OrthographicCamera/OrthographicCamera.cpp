#include "d3dpch.h"
#include "OrthographicCamera.h"
OrthographicCamera::OrthographicCamera(float x, float y, float p_Width, float p_Height)
{
	size.width = p_Width;
	size.height = p_Height;
	position.x = x;
	position.y = y;
	D3DXMatrixIdentity(&worldToViewportMat);
	UpdateWorldToViewportMat();
}

void OrthographicCamera::SetPosition(float p_X, float p_Y, float p_Z) 
{ 
	position.x = p_X;
	position.y = p_Y;
	position.z = p_Z;
	UpdateWorldToViewportMat();
}

void OrthographicCamera::SetPosition(const D3DXVECTOR3 &pos)
{
	position = pos;
	UpdateWorldToViewportMat();
}

void OrthographicCamera::AddPosition(float p_X, float p_Y, float p_Z)
{
	position.x += p_X;
	position.y += p_Y;
	position.z += p_Z;
	UpdateWorldToViewportMat();
}

void OrthographicCamera::AddPosition(const D3DXVECTOR3& pos)
{
	position += pos;
	UpdateWorldToViewportMat();
}

D3DXVECTOR3 OrthographicCamera::GetPosition()
{ 
	return position;
}
void OrthographicCamera::SetSize(const Size& p_Size)
{
	size = p_Size;
}

Size OrthographicCamera::GetSize()
{
	return size;
}

void OrthographicCamera::UpdateWorldToViewportMat()
{
	worldToViewportMat._22 = -1.0f;
	worldToViewportMat._41 = -position.x;
	worldToViewportMat._42 = position.y;
}

D3DXMATRIX OrthographicCamera::GetWorldToViewportMat()
{
	return worldToViewportMat;
}

