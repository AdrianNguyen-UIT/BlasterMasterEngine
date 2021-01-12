#include "d3dpch.h"
#include "EnemyCrab.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Bullets/Enemy/EnemyCrabBullet/EnemyCrabBullet.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"

EnemyCrab::EnemyCrab(float x, float y, float xMove, float yMove, float fFirstAttackDelayTime)
	: Enemy(x, y)
{
	name = "Crab";
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	horizontalMove = xMove;
	verticalMove = yMove;
	firstAttackDelayTime = fFirstAttackDelayTime;
}

void EnemyCrab::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 19;
	int spriteHeight = 16;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };
	std::shared_ptr<Animation> crabFly = std::make_shared<Animation>("Crab Fly");
	{
		crabFly->SetAnimationFPS(10);

		rect.left = 84;
		rect.top = 406;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;

		keyFrame.rect = rect;
		crabFly->AddKeyFrames(keyFrame);
		animationController->AddAnimation(crabFly);
		animationController->SetDefaultAnimation(crabFly);
	}

	std::shared_ptr<Animation> crabAttack = std::make_shared<Animation>("Crab Attack");
	{
		crabAttack->SetAnimationFPS(10);
		
		rect.left = 104;
		rect.top = 406;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		
		keyFrame.rect = rect;
		crabAttack->AddKeyFrames(keyFrame);
		animationController->AddAnimation(crabAttack);
	}


	std::shared_ptr<Parameter<bool>> isWaitingAfterAttack = std::make_shared<Parameter<bool>>("isWaitingAfterAttack");
	{
		animationController->AddBoolParameter(isWaitingAfterAttack);
	}

	std::shared_ptr<TransitionCondition<bool>> isWaitingAfterAttackTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isWaitingAfterAttackTrueBoolCond->SetParameter(isWaitingAfterAttack);
		isWaitingAfterAttackTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isWaitingAfterAttackFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isWaitingAfterAttackFalseBoolCond->SetParameter(isWaitingAfterAttack);
		isWaitingAfterAttackFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<Parameter<bool>> isAttacking = std::make_shared<Parameter<bool>>("isAttacking");
	{
		animationController->AddBoolParameter(isAttacking);
	}

	std::shared_ptr<TransitionCondition<bool>> isAttackingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAttackingTrueBoolCond->SetParameter(isAttacking);
		isAttackingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isAttackingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAttackingFalseBoolCond->SetParameter(isAttacking);
		isAttackingFalseBoolCond->SetValue(false);
	}


	std::shared_ptr<Transition> flyToAttackTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(crabFly),
		animationController->GetAnimationIndex(crabAttack));
	{
		flyToAttackTrans->AddBoolTransitionCondition(isAttackingTrueBoolCond);
		animationController->AddTransition(flyToAttackTrans);
	}

	std::shared_ptr<Transition> attackToFlyTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(crabAttack),
		animationController->GetAnimationIndex(crabFly));
	{
		attackToFlyTrans->AddBoolTransitionCondition(isWaitingAfterAttackTrueBoolCond);
		animationController->AddTransition(attackToFlyTrans);
	}
}

void EnemyCrab::Start()
{
	rigidbody->mass = 3.0f;
	startWaitinAfterAttackgAt = 0.0f;
	startAttackingAt = 0.0f;
	isFacingRight = false;
	firstAttack = true;
	isWaitingAfterAttack = true;
	isAttacking = false;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 15.0f, 16.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	damage = 0;
	detectRange = 150.0f;
}

void EnemyCrab::Update()
{
	if (!DetectPlayer())
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		spriteRenderer->enable = false;
		return;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	spriteRenderer->enable = true;

	//MOVEMENT
	if (leftCollision != 0 || rightCollision != 0)
	{
		horizontalMove = -horizontalMove;
	}
	else if (upCollision != 0 || downCollision != 0)
	{
		verticalMove = -verticalMove;
	}
	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = verticalMove * Time::GetFixedDeltaTime();


	//ATTACK
	if (startWaitinAfterAttackgAt == 0.0f)
	{
		startWaitinAfterAttackgAt = Time::GetTime();
		isWaitingAfterAttack = true;
		isAttacking = false;
	}
	if (Time::GetTime() - startWaitinAfterAttackgAt >= (firstAttack ? firstAttackDelayTime : afterAttackDelayTime))
	{
		if (firstAttack == true)
		{
			firstAttack = false;
		}

		if (startAttackingAt == 0.0f)
		{
			startAttackingAt = Time::GetTime();
			isAttacking = true;
			isWaitingAfterAttack = false;
			D3DXVECTOR3 location = { transform->position.x, transform->position.y - 10.0f, 0.0f };
			crabBullet = std::make_shared<EnemyCrabBullet>();
			crabBullet->CreateResources();
			SceneManager::Instantiate(crabBullet, location);
		}

		if (Time::GetTime() - startAttackingAt >= attackingDelayTime)
		{
			startAttackingAt = 0.0f;
			isAttacking = false;
			startWaitinAfterAttackgAt = 0.0f;
			isWaitingAfterAttack = true;
		}
	}


	//ANIMATION TRANS COND
	animationController->SetBool("isWaitingAfterAttack", isWaitingAfterAttack);
	animationController->SetBool("isAttacking", isAttacking);


	//FLIP COND
	if (horizontalMove > 0 && !isFacingRight)
	{
		Flip();
	}
	else if (horizontalMove < 0 && isFacingRight)
	{
		Flip();
	}
}

void EnemyCrab::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		std::shared_ptr<Sophia> sophia = std::dynamic_pointer_cast<Sophia>(object);
		if (sophia != NULL)
		{
			sophia->TakeDamage(damage);
		}

		std::shared_ptr<Jason> jason = std::dynamic_pointer_cast<Jason>(object);
		if (jason != NULL)
		{
			jason->TakeDamage(damage);
		}
	}
}

void EnemyCrab::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void EnemyCrab::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}