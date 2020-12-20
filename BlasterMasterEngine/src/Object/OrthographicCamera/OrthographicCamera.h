#pragma once
#include "Component/Component.h"
class OrthographicCamera
{
public:
	OrthographicCamera(float x, float y, float p_Width, float p_Height);

	void SetPosition(float p_X, float p_Y, float p_Z);
	void SetPosition(const D3DXVECTOR3 &pos);
	void AddPosition(float p_X, float p_Y, float p_Z);
	void AddPosition(const D3DXVECTOR3& pos);
	D3DXVECTOR3 GetPosition();

	void SetSize(const Size& p_Size);
	Size GetSize();
	D3DXMATRIX GetWorldToViewportMat();
	void MoveCamera(float x, float y, float z);
private:
	D3DXVECTOR3 position;
	Size size;
	D3DXMATRIX worldToViewportMat;

private:
	void UpdateWorldToViewportMat();
};