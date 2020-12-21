#include "d3dpch.h"
#include "AnimationController.h"


AnimationController::AnimationController()
{
	currentAnimationIndex = 0;
	playCurrentAnimation = true;
	forward = true;
	enable = true;
}


std::shared_ptr<Animation> &AnimationController::GetCurrentAnimation()
{
	return animations[currentAnimationIndex];
}

void AnimationController::AddAnimation(std::shared_ptr<Animation>&animation)
{
	animations.emplace_back(animation);
}

void AnimationController::SetBool(std::string p_Name, bool p_Value)
{
	for (size_t index = 0; index < boolParameters.size(); index++)
	{
		if (boolParameters[index]->GetName() == p_Name)
		{
			boolParameters[index]->SetValue(p_Value);
		}
	}
}

void AnimationController::SetInt(std::string p_Name, int p_Value)
{
	for (size_t index = 0; index < intParameters.size(); index++)
	{
		if (intParameters[index]->GetName() == p_Name)
		{
			intParameters[index]->SetValue(p_Value);
		}
	}
}

void AnimationController::SetFloat(std::string p_Name, float p_Value)
{
	for (size_t index = 0; index < floatParameters.size(); index++)
	{
		if (floatParameters[index]->GetName() == p_Name)
		{
			floatParameters[index]->SetValue(p_Value);
		}
	}
}

bool AnimationController::GetBool(std::string p_Name)
{
	for (size_t index = 0; index < boolParameters.size(); index++)
	{
		if (boolParameters[index]->GetName() == p_Name)
		{
			return boolParameters[index]->GetValue();
		}
	}
	return false;
}

int AnimationController::GetInt(std::string p_Name)
{
	for (size_t index = 0; index < intParameters.size(); index++)
	{
		if (intParameters[index]->GetName() == p_Name)
		{
			return intParameters[index]->GetValue();
		}
	}

	return -1;
}

float AnimationController::GetFloat(std::string p_Name)
{
	for (size_t index = 0; index < floatParameters.size(); index++)
	{
		if (floatParameters[index]->GetName() == p_Name)
		{
			return floatParameters[index]->GetValue();
		}
	}
	return -1.0f;
}


void AnimationController::SetDefaultAnimation(std::shared_ptr<Animation> &p_Animation)
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

void AnimationController::AddTransition(std::shared_ptr<Transition> &p_Transition)
{
	transitions.emplace_back(p_Transition);
}

void AnimationController::PauseAnimation()
{
	playCurrentAnimation = false;
}

void AnimationController::PlayAnimation(bool p_Forward)
{
	playCurrentAnimation = true;
	forward = p_Forward;
}

void AnimationController::PlayCurrentAnimation()
{
	for (size_t index = 0; index < animations.size(); index++)
	{
		if (index == currentAnimationIndex)
		{
			animations[index]->Play(forward, !playCurrentAnimation);
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
			if (!animations[currentAnimationIndex]->GetHasExitTime() || (
				animations[currentAnimationIndex]->GetHasExitTime() &&
				animations[currentAnimationIndex]->IsFinished()))
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
}

void AnimationController::Update()
{
	CheckTransition();
	PlayCurrentAnimation();
}

int AnimationController::GetAnimationIndex(std::shared_ptr<Animation> &animation)
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

void AnimationController::AddBoolParameter(std::shared_ptr<Parameter<bool>> &parameter)
{
	boolParameters.emplace_back(parameter);
}

void AnimationController::AddIntParameter(std::shared_ptr<Parameter<int>> &parameter)
{
	intParameters.emplace_back(parameter);
}

void AnimationController::AddFloatParameter(std::shared_ptr<Parameter<float>> &parameter)
{
	floatParameters.emplace_back(parameter);
}