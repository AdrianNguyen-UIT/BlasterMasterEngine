#pragma once
#include "Object/Object.h"
class Enemy : public Object2D
{
protected:
	int damage;
	float detectRange;
	std::shared_ptr<Object2D> sophia;
	std::shared_ptr<Object2D> jason;
private:
	bool sophiaRetrieve;
	bool jasonRetrieve;
public:
	Enemy(float x = 0, float y = 0);

	virtual void Die();
	virtual bool DetectPlayer();
	int GetDamage() { return damage; }

private:
	float Distance(D3DXVECTOR3 origin, D3DXVECTOR3 target);
};