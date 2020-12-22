#include "d3dpch.h"
#include "Rigidbody.h"

D3DXVECTOR2 Physic::gravity = { 0.0f, -9.81f };


Rigidbody::Rigidbody(const BodyType &p_BodyType, const D3DXVECTOR2 &p_Velocity )
	: bodyType(p_BodyType), velocity(p_Velocity)
{
	gravityForce = { 0.0f, 0.0f };
	externalForce = { 0.0f, 0.0f };
	totalForce = { 0.0f, 0.0f };
	mass = 1.0f;
	bodyType = BodyType::Dynamic;
	bounciness = 0.03f;
	gravityScale = 1.0f;
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::AddForce(const D3DXVECTOR2 &force)
{
	if (bodyType == BodyType::Dynamic)
	{
		externalForce += force;
	}
}

void Rigidbody::UpdateForce()
{
	gravityForce = mass * Physic::gravity * gravityScale;
	totalForce = gravityForce + externalForce;

	D3DXVECTOR2 acceleration = totalForce / mass;
	velocity += acceleration * Time::GetFixedDeltaTime();

	externalForce = { 0.0f, 0.0f };
}