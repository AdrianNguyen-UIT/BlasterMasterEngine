#pragma once
#include "Core/Time/Time.h"
#include "Component/Transform/Transform.h"

struct KeyFrame
{
	RECT rect;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;

	KeyFrame(const RECT &p_Rect = { 0, 0, 0, 0 },
		const D3DXVECTOR3& p_Position = { 0.0f, 0.0f, 0.0f },
		const D3DXVECTOR3& p_Rotation = { 0.0f, 0.0f, 0.0f },
		const D3DXVECTOR3& p_Scale = { 1.0f, 1.0f, 1.0f })
		: rect(p_Rect), position(p_Position), rotation(p_Rotation), scale(p_Scale)
	{
	}
};

class Animation
{
public:
	Animation(std::string p_Name = "Animation", int p_FramePerSecond = 24, bool p_IsLooping = true);

	float GetFrameTime() { return frameTime; }
	RECT GetCurrentFrameRect();
	D3DXVECTOR3 GetCurrentFramePosition();
	D3DXVECTOR3 GetCurrentFrameRotation();
	D3DXVECTOR3 GetCurrentFrameScale();
	void Play(bool forward = true, bool pause = false);
	void Reset();
	void SetAnimationFPS(int p_FramePerSecond);
	void SetIsLooping(bool enable);
	void SetAllowPause(bool allow);
	bool GetHasExitTime() { return hasExitTime; }
	void SetHasExitTime(bool doHave);
	std::string GetName() { return name; }
	void AddKeyFrames(const KeyFrame &p_KeyFrame);
	bool IsFinished();
	void SetInitFrameIndex(int frameIndex);
	void SetAllowBackward(bool allow);
private:
	std::string name;
	std::vector<KeyFrame> keyFrames;
	int framePerSecond;
	float frameTime;
	int currentFrameIndex;
	float currentFrameTime;
	bool isLooping;
	bool hasExitTime;
	bool allowPause;
	bool isFinished;
	bool initFrameIndex;
	bool allowBackward;
};