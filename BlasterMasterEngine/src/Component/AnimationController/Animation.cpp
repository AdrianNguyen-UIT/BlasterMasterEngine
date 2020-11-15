#include "d3dpch.h"
#include "Animation.h"

Animation::Animation(std::string p_Name, int p_FramePerSecond, bool p_IsLooping)
	: name(p_Name), framePerSecond(p_FramePerSecond), isLooping(p_IsLooping)
{
	frameTime = 1.0f / p_FramePerSecond;
	hasExitTime = false;
	allowPause = true;
	initFrameIndex = 0;
	allowBackward = false;
	Reset();
}

RECT Animation::GetCurrentFrameRect()
{
	return keyFrames[currentFrameIndex].rect;
}
D3DXVECTOR3 Animation::GetCurrentFramePosition()
{
	return keyFrames[currentFrameIndex].position;
}

D3DXVECTOR3 Animation::GetCurrentFrameRotation()
{
	return keyFrames[currentFrameIndex].rotation;
}

D3DXVECTOR3 Animation::GetCurrentFrameScale()
{
	return keyFrames[currentFrameIndex].scale;
}

void Animation::Play(bool forward, bool pause)
{
	if (pause && allowPause)
		return;

	currentFrameTime += Time::GetDeltaTime();
	if (currentFrameTime >= frameTime)
	{
		if (forward || !allowBackward)
		{
			++currentFrameIndex;
			if (currentFrameIndex == keyFrames.size())
			{
				if (isLooping)
				{
					currentFrameIndex = 0;
				}
				else
				{
					currentFrameIndex = keyFrames.size() - 1;
					isFinished = true;
				}
			}
		}
		else
		{
			--currentFrameIndex;
			if (currentFrameIndex < 0)
			{
				if (isLooping)
				{
					currentFrameIndex = keyFrames.size() - 1;
				}
				else
				{
					currentFrameIndex = 0;
					isFinished = true;
				}
			}
		}
		currentFrameTime = 0.0f;
	}
}

void Animation::Reset()
{
	currentFrameTime = 0.0f;
	currentFrameIndex = initFrameIndex;
	isFinished = false;
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

void Animation::AddKeyFrames(const KeyFrame& p_KeyFrame)
{
	keyFrames.emplace_back(p_KeyFrame);
}

void Animation::SetHasExitTime(bool doHave)
{
	hasExitTime = doHave;
}

bool Animation::IsFinished()
{
	return isFinished;
}

void Animation::SetAllowPause(bool allow)
{
	allowPause = allow;
}

void Animation::SetInitFrameIndex(int frameIndex)
{
	initFrameIndex = frameIndex;
	Reset();
}

void Animation::SetAllowBackward(bool allow)
{
	allowBackward = allow;
}