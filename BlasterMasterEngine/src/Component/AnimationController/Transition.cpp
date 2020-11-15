#include "d3dpch.h"
#include "Transition.h"

Transition::Transition(int p_Source, int p_Des)
	: sourceAnimationIndex(p_Source), desAnimationIndex(p_Des)
{
}

bool Transition::MeetCondition()
{
	return (MeetBoolCondition() && MeetIntCondition() && MeetFloatCondition());
}

bool Transition::MeetBoolCondition()
{
	for (size_t index = 0; index < boolTransitionCondition.size(); index++)
	{
		if (boolTransitionCondition[index]->GetParameter()->GetValue() != boolTransitionCondition[index]->GetValue())
			return false;
	}
	return true;
}

bool Transition::MeetIntCondition()
{
	for (size_t index = 0; index < intTransitionCondition.size(); index++)
	{
		if (intTransitionCondition[index]->GetCondition() == Condition::Less)
		{
			if (intTransitionCondition[index]->GetParameter()->GetValue() >= intTransitionCondition[index]->GetValue())
				return false;
		}
		else
		{
			if (intTransitionCondition[index]->GetParameter()->GetValue() <= intTransitionCondition[index]->GetValue())
				return false;
		}
	}
	return true;
}

bool Transition::MeetFloatCondition()
{
	for (size_t index = 0; index < floatTransitionCondition.size(); index++)
	{
		if (floatTransitionCondition[index]->GetCondition() == Condition::Less)
		{
			if (floatTransitionCondition[index]->GetParameter()->GetValue() >= floatTransitionCondition[index]->GetValue())
				return false;
		}
		else
		{
			if (floatTransitionCondition[index]->GetParameter()->GetValue() <= floatTransitionCondition[index]->GetValue())
				return false;
		}
	}
	return true;
}

void Transition::AddBoolTransitionCondition(std::shared_ptr<TransitionCondition<bool>>&p_TransitionCondition)
{
	boolTransitionCondition.emplace_back(p_TransitionCondition);
}

void Transition::AddIntTransitionCondition(std::shared_ptr<TransitionCondition<int>>&p_TransitionCondition)
{
	intTransitionCondition.emplace_back(p_TransitionCondition);
}

void Transition::AddFloatTransitionCondition(std::shared_ptr<TransitionCondition<float>>&p_TransitionCondition)
{
	floatTransitionCondition.emplace_back(p_TransitionCondition);
}