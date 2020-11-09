#include "d3dpch.h"
#include "Animation.h"

Animation::Animation(std::wstring p_Name, int p_FramePerSecond, bool p_IsLooping)
	: name(p_Name), framePerSecond(p_FramePerSecond), isLooping(p_IsLooping)
{
	frameTime = 1.0f / p_FramePerSecond;
	Reset();
}

RECT Animation::GetCurrentFrameRect()
{
	return rects[currentFrameIndex];
}

void Animation::Play()
{
	currentFrameTime += Time::GetDeltaTime();
	if (currentFrameTime >= frameTime)
	{
		++currentFrameIndex;
		if (isLooping)
		{
			if (currentFrameIndex >= rects.size())
			{
				currentFrameIndex = 0;
			}
		}
		currentFrameTime = 0.0f;
	}
}

void Animation::Reset()
{
	currentFrameTime = 0.0f;
	currentFrameIndex = 0;
}

void Animation::SetAnimationFPS(int p_FramePerSecond)
{
	framePerSecond = p_FramePerSecond;
	frameTime = 1.0f / p_FramePerSecond;
}

void Animation::SetIsLooping(bool enable)
{
	isLooping = enable;
}

void Animation::AddRect(RECT p_Rect)
{
	rects.emplace_back(p_Rect);
}