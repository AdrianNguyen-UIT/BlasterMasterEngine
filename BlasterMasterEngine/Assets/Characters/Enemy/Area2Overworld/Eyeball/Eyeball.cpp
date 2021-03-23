#include "d3dpch.h"
#include "Eyeball.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Bullets/Enemy/TeleporterBullet/TeleporterBullet.h"

Eyeball::Eyeball(float x, float y)
	: Enemy(x, y)
{
	name = "Eyeball";
}

void Eyeball::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 16;
	int spriteHeight = 16;

	KeyFrame keyFrame;
	RECT rect = { 0, 0, 0, 0 };
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> eyeballIdle = std::make_shared<Animation>("Eyeball Idle");
	{
		eyeballIdle->SetAnimationFPS(6);

		rect.left = 119;
		rect.top = 550;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		keyFrame.rect = rect;

		eyeballIdle->AddKeyFrames(keyFrame);

		animationController->AddAnimation(eyeballIdle);

		animationController->SetDefaultAnimation(eyeballIdle);
	}

	std::shared_ptr<Animation> eyeballAttack = std::make_shared<Animation>("Eyeball Attack");
	{
		eyeballAttack->SetAnimationFPS(6);

		for (size_t index = 0; index < 2; index++)
		{
			rect.left = 102 + (int)index * 34;
			rect.top = 550;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			eyeballAttack->AddKeyFrames(keyFrame);
		}

		animationController->AddAnimation(eyeballAttack);
	}

	std::shared_ptr<Parameter<bool>> isAttack = std::make_shared<Parameter<bool>>("isAttack");
	{
		animationController->AddBoolParameter(isAttack);
	}

	std::shared_ptr<TransitionCondition<bool>> isAttackTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAttackTrueBoolCond->SetParameter(isAttack);
		isAttackTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isAttackFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isAttackFalseBoolCond->SetParameter(isAttack);
		isAttackFalseBoolCond->SetValue(false);
	}

	//tan cong xong dung yen
	std::shared_ptr<Transition> attackingToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(eyeballAttack),
		animationController->GetAnimationIndex(eyeballIdle));
	{
		attackingToIdleTrans->AddBoolTransitionCondition(isAttackFalseBoolCond);
		animationController->AddTransition(attackingToIdleTrans);
	}

	//dung yen xong tan cong
	std::shared_ptr<Transition> idleToAttackTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(eyeballIdle),
		animationController->GetAnimationIndex(eyeballAttack));
	{
		idleToAttackTrans->AddBoolTransitionCondition(isAttackTrueBoolCond);
		animationController->AddTransition(idleToAttackTrans);
	}
}

void Eyeball::Start()
{
	Enemy::Start();

	srand(time(NULL));
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 24.0f, 32.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = true;
	attackStateDelay = 3.0f;
	transform->scale = { -3.0f, 3.0f, 3.0f };
	rigidbody->gravityScale = 0.0f;
	isAttack = false;
	idleStateDelay = 0.5f;
	attackStateDelay = 2.0f;
	currentIdleStateTime = 0.0f;
	currentAttackStateTime = 0.0f;
	randomDestMaxX = 50.0f;
	randomDestMaxY = 50.0f;
	randomDestMinX = 20.0f;
	randomDestMinY = 20.0f;
	destX = 0;
	destY = 0;

	damage = 2;
}

void Eyeball::Update()
{
	if (!IsInCameraBound()) {
		spriteRenderer->enable = false;
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		return;
	}
	else {
		spriteRenderer->enable = true;
		rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	}

	testY = transform->position.y;
	AttackCheck();
	SetAnimationParameter();
}

void Eyeball::AttackCheck()
{
	if (isAttack == false)
	{
		currentIdleStateTime += Time::GetDeltaTime();
		if (currentIdleStateTime >= idleStateDelay)
		{
			isAttack = true;
			Attack();
			SetTrajectory();
			currentIdleStateTime = 0.0f;
		}
	}
	if (isAttack == true)
	{
		Move();
		currentAttackStateTime += Time::GetDeltaTime();
		if (currentAttackStateTime >= attackStateDelay)
		{
			isAttack = false;
			currentAttackStateTime = 0.0f;
		}
	}
}

void Eyeball::Attack()
{
	float dx = 0;
	float dy = 0;
	TranslateDirection(dx, dy);
	D3DXVECTOR3 location = { transform->position.x, transform->position.y - 10.0f, 0.0f };
	std::shared_ptr<Object2D> bullet = std::make_shared<TeleporterBullet>(dx, dy);
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, location);
}

void Eyeball::TranslateDirection(float& x, float& y)
{
	if (player == NULL)
	{
		player = SceneManager::GetActiveScene()->FinObjectByName("OverworldJason");
	}
	else
	{
		float playerPositionX = player->transform->position.x;
		float playerPositionY = player->transform->position.y;
		float telerporterPositionX = transform->position.x;
		float telerporterPositionY = transform->position.y;
		float vectorX = playerPositionX - telerporterPositionX;
		float vectorY = playerPositionY - telerporterPositionY;
		if ((vectorX != 0) && (vectorY != 0))
		{
			float degree = (180.0f * atan(abs(vectorX) / abs(vectorY)) / 3.1415f);
			if (vectorX > 0)
				x = sin(degree * 3.1415f / 180);
			else x = -sin(degree * 3.1415f / 180);
			if (vectorY > 0)
				y = cos(degree * 3.1415f / 180);
			else y = -cos(degree * 3.1415f / 180);
		}
		else
		{
			if (vectorX == 0)
			{
				x = 0;
				if (vectorY > 0)
					y = 1;
				else y = -1;
			}
			if (vectorY == 0)
			{
				y = 0;
				if (vectorX > 0)
					x = 1;
				else x = -1;
			}
		}
	}
}

void Eyeball::TranslateDirection(float& x, float& y, float posX, float posY)
{
	float vectorX = posX - transform->position.x;
	float vectorY = posY - transform->position.y;
	if ((vectorX != 0) && (vectorY != 0))
	{
		float degree = (180.0f * atan(abs(vectorX) / abs(vectorY)) / 3.1415f);
		if (vectorX > 0)
			x = sin(degree * 3.1415f / 180);
		else x = -sin(degree * 3.1415f / 180);
		if (vectorY > 0)
			y = cos(degree * 3.1415f / 180);
		else y = -cos(degree * 3.1415f / 180);
	}
	else
	{
		if (vectorX == 0)
		{
			x = 0;
			if (vectorY > 0)
				y = 1;
			else y = -1;
		}
		if (vectorY == 0)
		{
			y = 0;
			if (vectorX > 0)
				x = 1;
			else x = -1;
		}
	}
}

void Eyeball::Move()
{
	radiant += Time::GetDeltaTime() * 3.1415 / attackStateDelay;
	transform->position.x = centerPointX + cos(radiant)*radius;
	transform->position.y = centerPointY + sin(radiant)*radius;
}

void Eyeball::SetTrajectory()
{
	if (player == NULL)
	{
		player = SceneManager::GetActiveScene()->FinObjectByName("OverworldJason");
	}
	float vectorX = player->transform->position.x - transform->position.x;
	float vectorY = player->transform->position.y - transform->position.y;
	destX = (rand() % (int)(randomDestMaxX - randomDestMinX)) + randomDestMinX;
	destY = (rand() % (int)(randomDestMaxY - randomDestMinY)) + randomDestMinY;
	if (vectorX < 0)
		destX = transform->position.x - destX;
	else
		destX = transform->position.x + destX;
	if (vectorY < 0)
		destY = transform->position.y - destY;
	else
		destY = transform->position.y + destY;
	centerPointX = (destX + transform->position.x) / 2;
	centerPointY = (destY + transform->position.y) / 2;
	radius = sqrt(vectorX*vectorX + vectorY*vectorY)/2;
	radiant = asin((transform->position.y - centerPointY) / radius);
	if ((transform->position.y > centerPointY) && (transform->position.x > centerPointX))
	{
		radiant = asin((transform->position.y - centerPointY) / radius);
	}
	if ((transform->position.y > centerPointY)&&(transform->position.x < centerPointX))
	{
		radiant += 3.1415 / 2 + asin((transform->position.y - centerPointY) / radius);
	}
	if ((transform->position.y < centerPointY) && (transform->position.x < centerPointX))
	{
		radiant += 2 * 3.1415 / 2 + asin((transform->position.y - centerPointY) / radius);
	}
	if ((transform->position.y < centerPointY) && (transform->position.x > centerPointX))
	{
		radiant += 3 * 3.1415 / 2 + asin((transform->position.y - centerPointY) / radius);
	}
}

void Eyeball::SetAnimationParameter()
{
	animationController->SetBool("isAttack", isAttack);
}