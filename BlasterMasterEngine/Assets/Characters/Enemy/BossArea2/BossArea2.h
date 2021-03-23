#pragma once
#include "BossPart.h"
#include "Object/Object.h"

class BossArea2 : public Object2D
{
private:

	enum class State
	{
		Hide,
		Appear,
		Attack,
		Die,
		Disappear
	};

	bool isAppear;
	bool isAttack = FALSE;
	bool isDie;
	bool isDisappear;

	bool startBossMusic = TRUE;

	float runSpeed_Hand;
	float runspeed_Boss;

	float default_RunSpeed_Hand;
	float default_RunSpeed_Boss;

	bool iFrame_Damage;
	int health = 1;

	// index attack coordinates
	int indexCurrenAtttackLeftHand;
	int indexCurrenAtttackRightHand;

	D3DXVECTOR2 distanceRightHandToAttack;
	D3DXVECTOR2 distanceLeftHandToAttack;

	std::array<Color, 4> iFrameColors_Damage;
	std::array<Color, 4> iFrameColors_Appear;

	State state;
	float timeBossAppeared;
	float timeBeforeDisappear;
	RECT moveBound;
	float time;
	float reversingDelay = 300.0f; //milisecond

	std::shared_ptr<BossPart> body;
	std::array<std::shared_ptr<BossPart>, 4> leftArmParts;
	std::array<std::shared_ptr<BossPart>, 4> rightArmParts;
	std::shared_ptr<BossPart> leftHand;
	std::shared_ptr<BossPart> rightHand;
	std::vector<D3DXVECTOR2> attackCoordinates_RightHand;
	std::vector<D3DXVECTOR2> attackCoordinates_LeftHand;

public:
	BossArea2(float x = 0, float y = 0);

	virtual void Start() override;
	virtual void Update() override;
	virtual void CreateResources() override;
	void SetMoveBound(RECT bound) { moveBound = bound; }
	bool GetIsDisappear() const { return isDisappear; }

private:
	void SetAnimationParameter();
	void Die();
	void DoIFrame_Damage();
	void DoIFrame_Appear();
	void DoIFrame_Disappear();
	void MoveHand();
	void MoveChildrenFollowBoss();
	void UpdateDirectionRightHand();
	void UpdateDirectionLeftHand();
	void Shoot();

	void FillColorForChildren();

public:
	void TakeDamage(int damage);
};
