#include "d3dpch.h"
#include "BossArea2.h"
#include "stdlib.h"   
#include "time.h" 

#include "BodyBoss.h"
#include "HandPart.h"
#include "LeftHandBoss.h"
#include "RightHandBoss.h"
#include "Assets/Bullets/Enemy/BossBullet/BossBullet.h"
#include "Assets/Particles/BossExplosion.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"
#include "Core/AudioMixer/AudioMixer.h"

BossArea2::BossArea2(float x, float y)
	: Object2D(x, y)
{
	name = "Boss Area 2";
	tag = Tag::Boss;
	layer = Layer::Enemy;
	rigidbody = GetComponent<Rigidbody>();

	// range move Rect
	moveBound.top = transform->position.y + 55;
	moveBound.left = transform->position.x - 95;
	moveBound.bottom = moveBound.top - 120;
	moveBound.right = moveBound.left + 190;
}

void BossArea2::CreateResources()
{

	{
		body = std::make_shared<BodyBoss>(0.0f, 0.0f);
		body->CreateResources();
		body->ownerObj = shared_from_this();
		SceneManager::Instantiate(std::dynamic_pointer_cast<Object2D>(body), body->transform->position);
	}

	{
		rightHand = std::make_shared<RightHandBoss>(25.0f, 0.0f);
		rightHand->CreateResources();
		rightHand->ownerObj = shared_from_this();
		SceneManager::Instantiate(std::dynamic_pointer_cast<Object2D>(rightHand), rightHand->transform->position);
	}

	{
		leftHand = std::make_shared<LeftHandBoss>(-25.0f, 0.0f);
		leftHand->CreateResources();
		leftHand->ownerObj = shared_from_this();
		SceneManager::Instantiate(std::dynamic_pointer_cast<Object2D>(leftHand), leftHand->transform->position);
	}

	{
		for (int i = 0; i < rightArmParts.size(); ++i)
		{
			rightArmParts[i] = std::make_shared<HandPart>(25.0f, 8.0f);
			rightArmParts[i]->CreateResources();
			std::dynamic_pointer_cast<HandPart>(rightArmParts[i])->isRightHand = true;
			rightArmParts[i]->ownerObj = shared_from_this();
			SceneManager::Instantiate(std::dynamic_pointer_cast<Object2D>(rightArmParts[i]), rightArmParts[i]->transform->position);
		}

		std::dynamic_pointer_cast<HandPart>(rightArmParts[0])->aheadPart = body;
		std::dynamic_pointer_cast<HandPart>(rightArmParts[0])->behindPart = rightArmParts[1];

		std::dynamic_pointer_cast<HandPart>(rightArmParts[1])->aheadPart = rightArmParts[0];
		std::dynamic_pointer_cast<HandPart>(rightArmParts[1])->behindPart = rightArmParts[2];

		std::dynamic_pointer_cast<HandPart>(rightArmParts[2])->aheadPart = rightArmParts[1];
		std::dynamic_pointer_cast<HandPart>(rightArmParts[2])->behindPart = rightArmParts[3];

		std::dynamic_pointer_cast<HandPart>(rightArmParts[3])->aheadPart = rightArmParts[2];
		std::dynamic_pointer_cast<HandPart>(rightArmParts[3])->behindPart = rightHand;
	}

	{
		for (int i = 0; i < leftArmParts.size(); ++i)
		{
			leftArmParts[i] = std::make_shared<HandPart>(-25.0f, 8.0f);
			leftArmParts[i]->CreateResources();
			std::dynamic_pointer_cast<HandPart>(leftArmParts[i])->isRightHand = false;
			leftArmParts[i]->ownerObj = shared_from_this();
			SceneManager::Instantiate(std::dynamic_pointer_cast<Object2D>(leftArmParts[i]), leftArmParts[i]->transform->position);
		}

		std::dynamic_pointer_cast<HandPart>(leftArmParts[0])->aheadPart = body;
		std::dynamic_pointer_cast<HandPart>(leftArmParts[0])->behindPart = leftArmParts[1];

		std::dynamic_pointer_cast<HandPart>(leftArmParts[1])->aheadPart = leftArmParts[0];
		std::dynamic_pointer_cast<HandPart>(leftArmParts[1])->behindPart = leftArmParts[2];

		std::dynamic_pointer_cast<HandPart>(leftArmParts[2])->aheadPart = leftArmParts[1];
		std::dynamic_pointer_cast<HandPart>(leftArmParts[2])->behindPart = leftArmParts[3];

		std::dynamic_pointer_cast<HandPart>(leftArmParts[3])->aheadPart = leftArmParts[2];
		std::dynamic_pointer_cast<HandPart>(leftArmParts[3])->behindPart = leftHand;
	}
	
}

void BossArea2::Start()
{
	default_RunSpeed_Boss = 30.0f;
	runspeed_Boss = 30.0f;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->bounciness = 0.0f;
	transform->scale = { WINDOW_CAMERA_SCALE_X ,WINDOW_CAMERA_SCALE_Y,0.0f };
	rigidbody->gravityScale = 0.0f;
	rigidbody->velocity = { runspeed_Boss * 3 / 4 * Time::GetFixedDeltaTime(), runspeed_Boss * -1 / 4 * Time::GetFixedDeltaTime() };
	state = State::Hide;
	health = 10;

	isAppear = false;
	isAttack = false;
	isDie = false;
	isDisappear = false;
	iFrame_Damage = false;
	timeBossAppeared = 0.0f;
	timeBeforeDisappear = 0.0f;
	default_RunSpeed_Hand = 100.0f;
	runSpeed_Hand = 100.0f;

	iFrameColors_Damage[0] = { 125, 124, 124, 255 };
	iFrameColors_Damage[1] = { 200, 200, 200, 255 };
	iFrameColors_Damage[2] = { 255, 255, 255, 255 };
	iFrameColors_Damage[3] = { 210, 150, 230, 255 };

	color = iFrameColors_Damage[2];

	iFrameColors_Appear[0] = { 0, 0, 0, 0 };
	iFrameColors_Appear[1] = { 20, 20, 20, 255 };
	iFrameColors_Appear[2] = { 100, 100, 100, 255 };
	iFrameColors_Appear[3] = { 195, 195, 195, 255 };

	distanceRightHandToAttack = { 0.0f,0.0f };
	distanceLeftHandToAttack = { 0.0f,0.0f };

	indexCurrenAtttackRightHand = 0;
	indexCurrenAtttackLeftHand = 0;

	{
		std::array<D3DXVECTOR2, 10> attackPositionList;
		attackPositionList[0] = { 80.0f,0.0f };
		attackPositionList[1] = { 80.0f,-80.0f };
		attackPositionList[2] = { 40.0f,-80.0f };
		attackPositionList[3] = { 0.0f,-80.0f };
		attackPositionList[4] = { -25.0f,-80.0f };
		attackPositionList[5] = { -25.0f,80.0f };
		attackPositionList[6] = { 0.0f,80.0f };
		attackPositionList[7] = { 80.0f,80.0f };
		attackPositionList[8] = { 0.0f,25.0f };
		attackPositionList[9] = { 0.0f,-40.0f };
		attackCoordinates_RightHand.emplace_back(attackPositionList[0]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[1]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[2]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[8]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[6]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[5]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[4]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[3]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[9]);
		attackCoordinates_RightHand.emplace_back(attackPositionList[7]);
	}

	{
		std::array<D3DXVECTOR2, 9> attackPositionList;
		attackPositionList[0] = { 25.0f,0.0f };
		attackPositionList[1] = { 25.0f,-25.0f };
		attackPositionList[2] = { 25.0f,-80.0f };
		attackPositionList[3] = { -80.0f,-80.0f };
		attackPositionList[4] = { -80.0f,-40.0f };
		attackPositionList[5] = { -80.0f,0.0f };
		attackPositionList[6] = { -80.0f,80.0f };
		attackPositionList[7] = { 25.0f,80.0f };
		attackPositionList[8] = { 25.0f,30.0f };
		attackCoordinates_LeftHand.emplace_back(attackPositionList[0]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[1]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[3]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[1]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[7]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[6]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[0]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[2]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[3]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[4]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[8]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[7]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[6]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[5]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[1]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[2]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[3]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[7]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[6]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[5]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[2]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[5]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[6]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[7]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[6]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[3]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[2]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[5]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[6]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[7]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[8]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[5]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[3]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[2]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[0]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[6]);
		attackCoordinates_LeftHand.emplace_back(attackPositionList[7]);
	}

}

void BossArea2::Update()
{
	if (timeBossAppeared >= 2.0f && timeBossAppeared < 5.0f)
	{
		isAppear = true;
		DoIFrame_Appear();
	}
	else if (timeBossAppeared >= 5.0f && !isDie)
	{
		if (startBossMusic)
		{
			AudioMixer::Stop("BOSS_INTRO");
			AudioMixer::PlayWaveFile("BOSS_THEME_1", true);
			startBossMusic = false; 
		}
		isAttack = true;
		if (rigidbody->velocity.x == 0.0f && rigidbody->velocity.y == 0.0f)
		{
			rigidbody->velocity = { runspeed_Boss * 3 / 4 * Time::GetFixedDeltaTime(), runspeed_Boss * -1 / 4 * Time::GetFixedDeltaTime() };
		}
		else
		{
			if (transform->position.x + 30.0f > moveBound.right || transform->position.x - 30.0f < moveBound.left) rigidbody->velocity.x *= -1;
			if (transform->position.y + 34.0f > moveBound.top || transform->position.y - 34.0f < moveBound.bottom) rigidbody->velocity.y *= -1;
		}

		static int numberBulletIsFired = 0;
		if (numberBulletIsFired < 4)
		{
			if (Time::GetTime() - time >= reversingDelay)
			{
				Shoot();
				time = Time::GetTime();
				numberBulletIsFired++;
			}
		}
		if (timeBossAppeared - ((int)(timeBossAppeared / 5.0f)) * 5.0f <= Time::GetDeltaTime() && numberBulletIsFired == 4)
		{
			numberBulletIsFired = 0;
		}

		MoveHand();
	}
	timeBossAppeared += Time::GetDeltaTime();

	if (!isAttack)
	{
		rigidbody->velocity.x = 0.0f;
		rigidbody->velocity.y = 0.0f;
		leftHand->rigidbody->velocity.x = 0.0f;
		leftHand->rigidbody->velocity.y = 0.0f;
		rightHand->rigidbody->velocity.x = 0.0f;
		rightHand->rigidbody->velocity.y = 0.0f;
	}

	if (isDie)
	{
		isAttack = false;
		AudioMixer::Stop("BOSS_THEME_1");
		if (timeBeforeDisappear <= 2 && (int)(timeBeforeDisappear / Time::GetFixedDeltaTime()) % 2 == 0)
		{
			int rangeX = 220;
			int rangeY = 150;
			int indexX = rand() % (rangeX + 1) + (-rangeX / 2);
			int indexY = rand() % (rangeY + 1) + (-rangeY / 2);
			std::shared_ptr<Object2D> explosion = std::make_shared<BossExplosion>(transform->position.x + indexX, transform->position.y + indexY);
			explosion->CreateResources();

			SceneManager::Instantiate(explosion, explosion->transform->position);
		}
		else if (timeBeforeDisappear > 3)
		{
			for (int i = 0; i < leftArmParts.size(); ++i)
			{
				SceneManager::DestroyObject(std::dynamic_pointer_cast<Object2D>(leftArmParts[i]));
			}

			for (int i = 0; i < rightArmParts.size(); ++i)
			{
				SceneManager::DestroyObject(std::dynamic_pointer_cast<Object2D>(rightArmParts[i]));
			}
			leftHand->color = color;
			rightHand->color = color;
			SceneManager::DestroyObject(std::dynamic_pointer_cast<Object2D>(body));
			SceneManager::DestroyObject(std::dynamic_pointer_cast<Object2D>(rightHand));
			SceneManager::DestroyObject(std::dynamic_pointer_cast<Object2D>(leftHand));
			SceneManager::DestroyObject(shared_from_this());
			isDisappear = true;
		}
		timeBeforeDisappear += Time::GetDeltaTime();
	}

	DoIFrame_Disappear();
	SetAnimationParameter();
	DoIFrame_Damage();
	FillColorForChildren();
	MoveChildrenFollowBoss();
}

void BossArea2::MoveHand()
{
	//// Right hand
	// update list position attack
	int healthLvl = health / 30;
	switch (healthLvl) {
	case 6:
	{
		attackCoordinates_RightHand[1] = { 80.0f,-70.0f };
		attackCoordinates_RightHand[2] = { 20.0f,-80.0f };
		break;
	}
	case 5:
	{
		attackCoordinates_RightHand[1] = { 80.0f,-70.0f };
		attackCoordinates_RightHand[2] = { 0.0f,-80.0f };
		attackCoordinates_RightHand[6] = { -25.0f,-40.0f };
		attackCoordinates_RightHand[8] = { 10.0f,-80.0f };
		break;
	}
	case 4:
	{
		attackCoordinates_RightHand[1] = { 80.0f,-70.0f };
		attackCoordinates_RightHand[2] = { 0.0f,-80.0f };
		attackCoordinates_RightHand[4] = { -25.0f,80.0f };
		attackCoordinates_RightHand[6] = { -25.0f,-70.0f };
		attackCoordinates_RightHand[8] = { 10.0f,-80.0f };
		break;
	}
	case 3:
	{
		attackCoordinates_RightHand[1] = { 40.0f,-80.0f };
		attackCoordinates_RightHand[2] = { 0.0f,-80.0f };
		attackCoordinates_RightHand[4] = { -25.0f,80.0f };
		attackCoordinates_RightHand[6] = { -25.0f,0.0f };
		attackCoordinates_RightHand[8] = { 40.0f,-80.0f };
		break;
	}
	case 2:
	{
		attackCoordinates_RightHand[0] = { 80.0f,80.0f };
		attackCoordinates_RightHand[1] = { 40.0f,-80.0f };
		attackCoordinates_RightHand[2] = { 0.0f,-80.0f };
		attackCoordinates_RightHand[4] = { -25.0f,80.0f };
		attackCoordinates_RightHand[6] = { -25.0f,80.0f };
		attackCoordinates_RightHand[8] = { 60.0f,-80.0f };
		break;
	}
	case 1:
	{
		attackCoordinates_RightHand[0] = { 80.0f,80.0f };
		attackCoordinates_RightHand[1] = { 0.0f,-80.0f };
		attackCoordinates_RightHand[2] = { 0.0f,-80.0f };
		attackCoordinates_RightHand[3] = { -10.0f,-80.0f };
		attackCoordinates_RightHand[4] = { -25.0f,80.0f };
		attackCoordinates_RightHand[6] = { -25.0f,80.0f };
		attackCoordinates_RightHand[8] = { 80.0f,-80.0f };
		break;
	}
	default: {}
	}

	distanceRightHandToAttack.x = attackCoordinates_RightHand[indexCurrenAtttackRightHand].x
		- (rightHand->transform->position.x - (transform->position.x + 25.0f));
	distanceRightHandToAttack.y = attackCoordinates_RightHand[indexCurrenAtttackRightHand].y
		- (rightHand->transform->position.y - (transform->position.y + 0.0f));

	// update direction for right hand
	if (abs(distanceRightHandToAttack.x) < 2.0f && abs(distanceRightHandToAttack.y) < 2.0f)
	{
		rightHand->transform->position.x = transform->position.x + 25.0f + attackCoordinates_RightHand[indexCurrenAtttackRightHand].x;
		rightHand->transform->position.y = transform->position.y + 0.0f + attackCoordinates_RightHand[indexCurrenAtttackRightHand].y;
		if (indexCurrenAtttackRightHand == (attackCoordinates_RightHand.size() - 1))
		{
			indexCurrenAtttackRightHand = 0;
		}
		else indexCurrenAtttackRightHand++;
	}
	UpdateDirectionRightHand();
	D3DXVECTOR3 oldPositionRightHand = rightHand->transform->position;
	std::dynamic_pointer_cast<HandPart>(rightArmParts[3])->MoveFollowBehindHandPart();

	// check limit move (coordinate attack > limit move then next coordinate)
	if (oldPositionRightHand != rightHand->transform->position)
	{
		if (indexCurrenAtttackRightHand == (attackCoordinates_RightHand.size() - 1))
		{
			indexCurrenAtttackRightHand = 0;
		}
		else indexCurrenAtttackRightHand++;
	}

	//// Left hand
	distanceLeftHandToAttack.x = attackCoordinates_LeftHand[indexCurrenAtttackLeftHand].x
		- (leftHand->transform->position.x - (transform->position.x - 25.0f));
	distanceLeftHandToAttack.y = attackCoordinates_LeftHand[indexCurrenAtttackLeftHand].y
		- (leftHand->transform->position.y - (transform->position.y - 0.0f));

	// update direction for Left hand
	if (abs(distanceLeftHandToAttack.x) < 2.0f && abs(distanceLeftHandToAttack.y) < 2.0f)
	{
		leftHand->transform->position.x = transform->position.x - 25.0f + attackCoordinates_LeftHand[indexCurrenAtttackLeftHand].x;
		leftHand->transform->position.y = transform->position.y + 0.0f + attackCoordinates_LeftHand[indexCurrenAtttackLeftHand].y;
		if (indexCurrenAtttackLeftHand == (attackCoordinates_LeftHand.size() - 1))
		{
			indexCurrenAtttackLeftHand = 0;
		}
		else indexCurrenAtttackLeftHand++;
	}
	UpdateDirectionLeftHand();
	D3DXVECTOR3 oldPositionLeftHand = leftHand->transform->position;
	std::dynamic_pointer_cast<HandPart>(leftArmParts[3])->MoveFollowBehindHandPart();

	// check limit move (coordinate attack > limit move then next coordinate)
	if (oldPositionLeftHand != leftHand->transform->position)
	{
		if (indexCurrenAtttackLeftHand == (attackCoordinates_LeftHand.size() - 1))
		{
			indexCurrenAtttackLeftHand = 0;
		}
		else indexCurrenAtttackLeftHand++;
	}
}

void BossArea2::MoveChildrenFollowBoss()
{
	body->transform->position.x += rigidbody->velocity.x;
	body->transform->position.y += rigidbody->velocity.y;
	for (int i = 0; i < leftArmParts.size(); ++i)
	{
		leftArmParts[i]->transform->position.x += rigidbody->velocity.x;
		leftArmParts[i]->transform->position.y += rigidbody->velocity.y;
	}

	for (int i = 0; i < rightArmParts.size(); ++i)
	{
		rightArmParts[i]->transform->position.x += rigidbody->velocity.x;
		rightArmParts[i]->transform->position.y += rigidbody->velocity.y;
	}
	leftHand->transform->position.x += rigidbody->velocity.x;
	leftHand->transform->position.y += rigidbody->velocity.y;
	rightHand->transform->position.x += rigidbody->velocity.x;
	rightHand->transform->position.y += rigidbody->velocity.y;
}

void BossArea2::UpdateDirectionRightHand()
{
	distanceRightHandToAttack.x = attackCoordinates_RightHand[indexCurrenAtttackRightHand].x
		- (rightHand->transform->position.x - transform->position.x - 25.0f);
	distanceRightHandToAttack.y = attackCoordinates_RightHand[indexCurrenAtttackRightHand].y
		- (rightHand->transform->position.y - transform->position.y - 0.0f);

	int totalVelocity = sqrt(pow(distanceRightHandToAttack.x, 2) + pow(distanceRightHandToAttack.y, 2));
	if (totalVelocity == 0) totalVelocity = 1;
	rightHand->rigidbody->velocity.x = distanceRightHandToAttack.x * Time::GetFixedDeltaTime() * (runSpeed_Hand / totalVelocity);
	rightHand->rigidbody->velocity.y = distanceRightHandToAttack.y * Time::GetFixedDeltaTime() * (runSpeed_Hand / totalVelocity);
}

void BossArea2::UpdateDirectionLeftHand()
{
	distanceLeftHandToAttack.x = attackCoordinates_LeftHand[indexCurrenAtttackLeftHand].x
		- (leftHand->transform->position.x - (transform->position.x - 25.0f));
	distanceLeftHandToAttack.y = attackCoordinates_LeftHand[indexCurrenAtttackLeftHand].y
		- (leftHand->transform->position.y - (transform->position.y - 0.0f));

	int totalVelocity = sqrt(pow(distanceLeftHandToAttack.x, 2) + pow(distanceLeftHandToAttack.y, 2));
	if (totalVelocity == 0) totalVelocity = 1;
	leftHand->rigidbody->velocity.x = distanceLeftHandToAttack.x * Time::GetFixedDeltaTime() * (runSpeed_Hand / totalVelocity);
	leftHand->rigidbody->velocity.y = distanceLeftHandToAttack.y * Time::GetFixedDeltaTime() * (runSpeed_Hand / totalVelocity);
}

void BossArea2::Shoot()
{
	AudioMixer::PlayWaveFile("BOSS_SHOOTING", false);
	std::shared_ptr<Object2D> bullet;
	D3DXVECTOR3 location;
	location = { transform->position.x, transform->position.y - 35.0f, 0.0f };
	bullet = std::make_shared<BossBullet>(location.x, location.y);
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, location);
}

void BossArea2::FillColorForChildren()
{
	// fill color for children
	body->color = color;
	for (int i = 0; i < leftArmParts.size(); ++i)
	{
		leftArmParts[i]->color = color;
	}

	for (int i = 0; i < rightArmParts.size(); ++i)
	{
		rightArmParts[i]->color = color;
	}
	leftHand->color = color;
	rightHand->color = color;
}

void BossArea2::DoIFrame_Damage()
{
	if (iFrame_Damage)
	{
		static float iFrameTime = 0.0f;
		static int iFrameColorIndex = 0;

		if (iFrameTime >= 0.45f)
		{
			runSpeed_Hand = default_RunSpeed_Hand;
			runspeed_Boss = default_RunSpeed_Boss;
			iFrameTime = 0.0f;
			iFrame_Damage = false;
			iFrameColorIndex = 0;
			color = iFrameColors_Damage[2];
		}
		else
		{
			runSpeed_Hand = default_RunSpeed_Hand / 10;
			runspeed_Boss = default_RunSpeed_Boss / 10;
			color = iFrameColors_Damage[iFrameColorIndex];
			++iFrameColorIndex;
			if (iFrameColorIndex > iFrameColors_Damage.size() - 1)
			{
				iFrameColorIndex = 0;
			}
			iFrameTime += Time::GetDeltaTime();
		}
	}
}

void BossArea2::DoIFrame_Appear()
{
	int indexFrameColor = (int)((timeBossAppeared - 2.0f)) + 1;
	int indexColor = (int)(((timeBossAppeared - 2.0f) / Time::GetFixedDeltaTime())) % 60;
	color = iFrameColors_Appear[indexFrameColor];
	color = Color(color.red + indexColor, color.red + indexColor, color.red + indexColor, 255);
}

void BossArea2::DoIFrame_Disappear()
{
	if (isDie)
	{
	}

}

void BossArea2::Die()
{
	AudioMixer::PlayWaveFile("BOSS_DIE", FALSE);
	for (std::shared_ptr<Object2D> child : childObjects)
	{
		child->enable = false;
	}
	state = State::Die;
	isDie = true;
}

void BossArea2::SetAnimationParameter()
{
	body->animationController->SetBool("Appear", isAppear);
	body->animationController->SetBool("Attack", isAttack);
	body->animationController->SetBool("Die", isDie);

	rightHand->animationController->SetBool("Appear", isAppear);
	rightHand->animationController->SetBool("Attack", isAttack);
	rightHand->animationController->SetBool("Die", isDie);

	leftHand->animationController->SetBool("Appear", isAppear);
	leftHand->animationController->SetBool("Attack", isAttack);
	leftHand->animationController->SetBool("Die", isDie);

	for (int i = 0; i < rightArmParts.size(); ++i)
	{
		rightArmParts[i]->animationController->SetBool("Appear", isAppear);
		rightArmParts[i]->animationController->SetBool("Attack", isAttack);
		rightArmParts[i]->animationController->SetBool("Die", isDie);
	}

	for (int i = 0; i < leftArmParts.size(); ++i)
	{
		leftArmParts[i]->animationController->SetBool("Appear", isAppear);
		leftArmParts[i]->animationController->SetBool("Attack", isAttack);
		leftArmParts[i]->animationController->SetBool("Die", isDie);
	}
}

void BossArea2::TakeDamage(int damage)
{
	if (isAttack)
	{
		//? PLay damage audio effect
		AudioMixer::PlayWaveFile("BOSS_HIT_1", false);
		health -= damage;

		if (health <= 0)
		{
			health = 0;
			Die();
		}
	}
}