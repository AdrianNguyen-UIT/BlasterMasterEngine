#pragma once

template <typename T>
struct Parameter
{
	std::wstring name;
	T value;

	Parameter(std::wstring p_Name = L"Parameter_00", T p_Value = 0)
		: name(p_Name), value(p_Value)
	{
	}
};

enum class Condition
{
	Default,
	Greater,
	Less
};

template <typename T>
struct TransitionCondition
{
	std::shared_ptr<Parameter<T>> parameter;
	Condition condition;
	T value;

	TransitionCondition() 
	{
		condition = Condition::Default;
		value = 0;
	}

	TransitionCondition(std::shared_ptr<Parameter<T>> p_Parameter, Condition p_Condition, T p_Value)
	{
		parameter = p_Parameter;
		condition = p_Condition;
		value = p_Value;
	}
};

class Transition
{
public:
	int sourceAnimationIndex;
	int desAnimationIndex;

private:
	std::vector<std::shared_ptr<TransitionCondition<bool>>> boolTransitionCondition;
	std::vector<std::shared_ptr<TransitionCondition<int>>> intTransitionCondition;
	std::vector<std::shared_ptr<TransitionCondition<float>>> floatTransitionCondition;

public:
	Transition(int p_Source = 0, int p_Des = 0);
	friend class AnimationController;

	void AddBoolTransitionCondition(std::shared_ptr<TransitionCondition<bool>> p_TransitionCondition);
	void AddIntTransitionCondition(std::shared_ptr<TransitionCondition<int>> p_TransitionCondition);
	void AddFloatTransitionCondition(std::shared_ptr<TransitionCondition<float>> p_TransitionCondition);

private:
	bool MeetCondition();
	bool MeetBoolCondition();
	bool MeetIntCondition();
	bool MeetFloatCondition();
};