#pragma once
#include "Core/Time/Time.h"

class Animation
{
public:
	Animation(std::wstring p_Name = L"Animation", int p_FramePerSecond = 24, bool p_IsLooping = true);

	float GetFrameTime() { return frameTime; }
	RECT GetCurrentFrameRect();
	void Play();
	void Reset();
	void SetAnimationFPS(int p_FramePerSecond);
	void SetIsLooping(bool enable);
	std::wstring GetName() { return name; }
	void AddRect(RECT p_Rect);

private:
	std::wstring name;
	std::vector<RECT> rects;
	int framePerSecond;
	float frameTime;
	int currentFrameIndex;
	float currentFrameTime;
	bool isLooping;
};