#pragma once
#include "Object/Object.h"
#include "Object/OrthographicCamera/OrthographicCamera.h"

class Enemy : public Object2D
{
protected:
	float horizontalMove;
	float verticalMove;
	bool isFacingRight;
	int damage;
	float detectRange;

	std::shared_ptr<Object2D> sophia;
	std::shared_ptr<Object2D> jason;
	std::shared_ptr<OrthographicCamera> camera;

public:
	Enemy(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Die();
	virtual bool DetectPlayer();
	virtual bool IsInCameraBound();
	virtual void OnCollisionEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnCollisionStay(std::shared_ptr<Object2D> object) override;

private:
	float Distance(D3DXVECTOR3 origin, D3DXVECTOR3 target);
	void DoDamage(std::shared_ptr<Object2D> object);

protected:
	void Flip();
};