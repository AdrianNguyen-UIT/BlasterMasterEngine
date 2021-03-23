#pragma once
#include "Core/SceneManager/Scene.h"
#include "Object/Object.h"
#include "Core/AudioMixer/AudioMixer.h"

class BossRoomArea2 : public Object2D
{

public:
	BossRoomArea2(float x = 0, float y = 0);

	virtual void Start() override;
	void Update() override;
	virtual void CreateResources() override;
	virtual void OnTriggerEnter(std::shared_ptr<Object2D> object) override;
	virtual void OnTriggerExit(std::shared_ptr<Object2D> object) override;

	void  SetState(bool EnableEnter = true, bool JoinedRoom = false, bool AlreadyAppear = false);

private:
	void Die();

	bool EnableEnterBossRoom;
	bool isJoinedBossRoom;
	bool isAlreadyAppear;
	bool isLoadBlackBackground;
	bool isDisappear;
	std::shared_ptr<Object2D> backgroundObj;
	std::shared_ptr<Object2D> boss;
	void CheckIsJoinedRoom();
	void DoIFrame_BeforBossAppear();
	void SetAnimationParameter();
};