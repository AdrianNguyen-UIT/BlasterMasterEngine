#include "d3dpch.h"
#include "Enemy.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Core/AudioMixer/AudioMixer.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Assets/Characters/Jason/OverworldJason.h"
Enemy::Enemy(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Enemy;
	layer = Layer::Enemy;

	damage = 0;
	detectRange = 0.0f;
	horizontalMove = 0.0f;
	verticalMove = 0.0f;
	isFacingRight = true;

	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void Enemy::Start()
{
	sophia = SceneManager::GetActiveScene()->FinObjectByName("Sophia");
	camera = SceneManager::GetActiveScene()->GetActiceCamera();
}

void Enemy::Die()
{
	AudioMixer::PlayWaveFile("ENEMY_DIE_NORMAL", FALSE);
	SceneManager::DestroyObject(shared_from_this());
}

bool Enemy::DetectPlayer()
{
	if (CharacterController::GetCharacterInControl() == Character::Sophia)
	{
		if (sophia != NULL)
		{
			if (Distance(transform->position, sophia->transform->position) <= detectRange)
			{
				return true;
			}
		}
		return false;
		
	}
	else
	{
		if (jason == NULL) 
		{
			jason = SceneManager::GetActiveScene()->FinObjectByName("Jason");
		}

		if (jason != NULL)
		{
			if (Distance(transform->position, jason->transform->position) <= detectRange)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

bool Enemy::IsInCameraBound()
{
	if (camera == NULL)
		return false;

	if (boxCollider->topLeft.x + boxCollider->size.width < camera->GetPosition().x ||
		boxCollider->topLeft.x > (camera->GetPosition().x + camera->GetSize().width) ||
		boxCollider->topLeft.y - boxCollider->size.height > camera->GetPosition().y ||
		boxCollider->topLeft.y < (camera->GetPosition().y - camera->GetSize().height))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Enemy::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
	DoDamage(object);
}

void Enemy::OnCollisionStay(std::shared_ptr<Object2D> object)
{
	DoDamage(object);
}

float Enemy::Distance(D3DXVECTOR3 origin, D3DXVECTOR3 target)
{
	float distance = (origin.x - target.x) * (origin.x - target.x) + (origin.y - target.y) * (origin.y - target.y);
	return sqrt(distance);
}

void Enemy::DoDamage(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		std::shared_ptr<OverworldJason> overworldJason = std::dynamic_pointer_cast<OverworldJason>(object);
		if (overworldJason != NULL)
		{
			overworldJason->TakeDamage(damage);
		}

		std::shared_ptr<Sophia> sophia = std::dynamic_pointer_cast<Sophia>(object);
		if (sophia != NULL)
		{
			sophia->TakeDamage(0);
		}

		std::shared_ptr<Jason> jason = std::dynamic_pointer_cast<Jason>(object);
		if (jason != NULL)
		{
			jason->TakeDamage(damage);
		}
	}
}


void Enemy::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}