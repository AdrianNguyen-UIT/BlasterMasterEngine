#include "d3dpch.h"
#include "Enemy.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
Enemy::Enemy(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Enemy;
	damage = 0;
	detectRange = 0.0f;	
	sophiaRetrieve = false;
	jasonRetrieve = false;
}

void Enemy::Die()
{
	SceneManager::DestroyObject(shared_from_this());
}

bool Enemy::DetectPlayer()
{
	if (CharacterController::GetCharacterInControl() == Character::Sophia)
	{
		if (!sophiaRetrieve)
		{
			sophia = SceneManager::GetActiveScene()->FinObjectByName("Sophia");
			if (sophia != NULL)
				sophiaRetrieve = true;
		}

		if (sophia != NULL)
		{
			if (Distance(transform->position, sophia->transform->position) <= detectRange)
				return true;
		}
		return false;
		
	}
	else
	{
		if (!jasonRetrieve)
		{
			jason = SceneManager::GetActiveScene()->FinObjectByName("Jason");
			if (jason != NULL)
				jasonRetrieve = true;
		}

		if (jason != NULL)
		{
			if (Distance(transform->position, jason->transform->position) <= detectRange)
				return true;
		}
		return false;
	}
	return false;
}

float Enemy::Distance(D3DXVECTOR3 origin, D3DXVECTOR3 target)
{
	float distance = (origin.x - target.x) * (origin.x - target.x) + (origin.y - target.y) * (origin.y - target.y);
	return sqrt(distance);
}