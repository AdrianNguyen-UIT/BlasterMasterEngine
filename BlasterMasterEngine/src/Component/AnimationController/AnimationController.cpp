#include "d3dpch.h"
#include "AnimationController.h"


AnimationController::AnimationController()
{
	currentAnimationIndex = 0;
}


std::shared_ptr<Animation> AnimationController::GetCurrentAnimation()
{
	return animations[currentAnimationIndex];
}

void AnimationController::AddAnimation(std::shared_ptr<Animation> animation)
{
	animations.emplace_back(animation);
}

void AnimationController::SetBool(std::wstring p_Name, bool p_Value)
{
	for (size_t index = 0; index < boolParameters.size(); index++)
	{
		if (boolParameters[index]->name == p_Name)
		{
			boolParameters[index]->value = p_Value;
		}
	}
}

void AnimationController::SetInt(std::wstring p_Name, int p_Value)
{
	for (size_t index = 0; index < intParameters.size(); index++)
	{
		if (intParameters[index]->name == p_Name)
		{
			intParameters[index]->value = p_Value;
		}
	}
}

void AnimationController::SetFloat(std::wstring p_Name, float p_Value)
{
	for (size_t index = 0; index < floatParameters.size(); index++)
	{
		if (floatParameters[index]->name == p_Name)
		{
			floatParameters[index]->value = p_Value;
		}
	}
}

bool AnimationController::GetBool(std::wstring p_Name)
{
	for (size_t index = 0; index < boolParameters.size(); index++)
	{
		if (boolParameters[index]->name == p_Name)
		{
			return boolParameters[index]->value;
		}
	}
	return false;
}

int AnimationController::GetInt(std::wstring p_Name)
{
	for (size_t index = 0; index < intParameters.size(); index++)
	{
		if (intParameters[index]->name == p_Name)
		{
			return intParameters[index]->value;
		}
	}

	return -1;
}

float AnimationController::GetFloat(std::wstring p_Name)
{
	for (size_t index = 0; index < floatParameters.size(); index++)
	{
		if (floatParameters[index]->name == p_Name)
		{
			return floatParameters[index]->value;
		}
	}
	return -1.0f;
}


void AnimationController::SetDefaultAnimation(std::shared_ptr<Animation> p_Animation)
{
	for (size_t index = 0; index < animations.size(); index++)
	{
		if (animations[index]->GetName() == p_Animation->GetName())
		{
			currentAnimationIndex = (int)index;
			return;
		}
	}
}

void AnimationController::AddTransition(std::shared_ptr<Transition> p_Transition)
{
	transitions.emplace_back(p_Transition);
}

void AnimationController::PlayCurrentAnimation()
{
	for (size_t index = 0; index < animations.size(); index++)
	{
		if (index == currentAnimationIndex)
		{
			animations[index]->Play();
			return;
		}
	}
}

void AnimationController::CheckTransition()
{
	for (size_t index = 0; index < transitions.size(); index++)
	{
		if (transitions[index]->sourceAnimationIndex == currentAnimationIndex)
		{
			if (transitions[index]->MeetCondition())
			{
				animations[currentAnimationIndex]->Reset();
				currentAnimationIndex = transitions[index]->desAnimationIndex;
				return;
			}
		}
	}
}

void AnimationController::Update()
{
	PlayCurrentAnimation();
	CheckTransition();
}

int AnimationController::GetAnimationIndex(std::shared_ptr<Animation> animation)
{
	for (size_t index = 0; index < animations.size(); index++)
	{
		if (animation->GetName() == animations[index]->GetName())
		{
			return (int)index;
		}
	}
	return -1;
}

void AnimationController::AddBoolParameter(std::shared_ptr<Parameter<bool>> parameter)
{
	boolParameters.emplace_back(parameter);
}

void AnimationController::AddIntParameter(std::shared_ptr<Parameter<int>> parameter)
{
	intParameters.emplace_back(parameter);
}

void AnimationController::AddFloatParameter(std::shared_ptr<Parameter<float>> parameter)
{
	floatParameters.emplace_back(parameter);
}