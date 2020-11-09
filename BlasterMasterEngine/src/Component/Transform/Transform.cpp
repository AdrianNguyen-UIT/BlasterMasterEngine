#include "d3dpch.h"
#include "Transform.h"

Transform::Transform(const D3DXVECTOR3& p_Position, const D3DXVECTOR3& p_Rotation, const D3DXVECTOR3& p_Scale)
	:position(p_Position), rotation(p_Rotation), scale(p_Scale)
{
	InitMatrix();
}


void Transform::Translate(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Transform::RotateX(float angle)
{
	rotation.x = angle;
}

void Transform::RotateY(float angle)
{
	rotation.y = angle;
}

void Transform::RotateZ(float angle)
{
	rotation.z = angle;
}

void Transform::Scale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void Transform::InitMatrix()
{
	D3DXMatrixIdentity(&translateMat);
	D3DXMatrixIdentity(&rotateXMat);
	D3DXMatrixIdentity(&rotateYMat);
	D3DXMatrixIdentity(&rotateZMat);
	D3DXMatrixIdentity(&scaleMat);
}

D3DXMATRIX Transform::GetTransformMatrix()
{ 
	return rotateXMat * rotateYMat * rotateZMat * scaleMat * translateMat;
}

void Transform::Update()
{
	D3DXMatrixTranslation(&translateMat, positionInVP.x, positionInVP.y, positionInVP.z);
	D3DXMatrixRotationX(&rotateXMat, D3DXToRadian(rotation.x));
	D3DXMatrixRotationY(&rotateYMat, D3DXToRadian(rotation.y));
	D3DXMatrixRotationZ(&rotateZMat, D3DXToRadian(rotation.z));
	D3DXMatrixScaling(&scaleMat, scale.x, scale.y, scale.z);
}


void Transform::TranslateWorldToViewport(const D3DXMATRIX& worldToViewportMat)
{
	D3DXVECTOR4 tempPos;
	D3DXVec3Transform(&tempPos, &position, &worldToViewportMat);
	positionInVP.x = tempPos.x;
	positionInVP.y = tempPos.y;
	positionInVP.z = tempPos.z;
}