#pragma once

class Transform
{
public:
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

private:
	D3DXMATRIX translateMat;
	D3DXMATRIX rotateXMat;
	D3DXMATRIX rotateYMat;
	D3DXMATRIX rotateZMat;
	D3DXMATRIX scaleMat;

	D3DXVECTOR3 positionInVP;

public:
	Transform(const D3DXVECTOR3& p_Position = { 0.0f, 0.0f, 0.0f },
		const D3DXVECTOR3& p_Rotation = { 0.0f, 0.0f, 0.0f },
		const D3DXVECTOR3& p_Scale = { 1.0f, 1.0f, 1.0f });

	void Translate(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	void RotateX(float angle = 0.0f);
	void RotateY(float angle = 0.0f);

	void RotateZ(float angle = 0.0f);

	void Scale(float x = 1.0f, float y = 1.0f, float z = 0.0f);

	D3DXMATRIX GetTransformMatrix();

	void Update();
	void TranslateWorldToViewport(const D3DXMATRIX& worldToViewportMat);
private:
	void InitMatrix();
};