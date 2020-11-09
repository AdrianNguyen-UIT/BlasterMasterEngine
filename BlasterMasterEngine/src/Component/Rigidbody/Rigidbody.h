#pragma once

struct Physic
{
	static D3DXVECTOR2 gravity;
};

class Rigidbody
{
public:

	enum class BodyType
	{
		Dynamic,
		Kinematic,
		Static
	};
	friend class Object2D;
public:
	BodyType bodyType;
	D3DXVECTOR2 velocity;
	float bounciness;
	float mass;
	float gravityScale;

private:
	D3DXVECTOR2 externalForce;
	D3DXVECTOR2 totalForce;
	D3DXVECTOR2 gravityForce;
private:
	void UpdateForce();

public:
	Rigidbody(const BodyType &p_BodyType = BodyType::Dynamic, const D3DXVECTOR2 &p_Velocity = {0.0f, 0.0f});
	~Rigidbody();

	void AddForce(const D3DXVECTOR2 &force = {0.0f, 0.0f});
};