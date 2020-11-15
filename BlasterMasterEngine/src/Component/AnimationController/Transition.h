#pragma once

template <typename T>
class Parameter
{
private:
	std::string name;
	T value;

public:
	Parameter(std::string p_Name = "Parameter_00", T p_Value = 0)
		: name(p_Name), value(p_Value)
	{
	}

	void SetName(std::string p_Name) { name = p_Name; }
	void SetValue(T p_Value) { value = p_Value; }
	std::string GetName() { return name; }
	T GetValue() { return value; }
};

enum class Condition
{
	Default,
	Greater,
	Less
};

template <typename T>
class TransitionCondition
{
private:
	std::shared_ptr<Parameter<T>> parameter;
	Condition condition;
	T value;

public:
	TransitionCondition(const std::shared_ptr<Parameter<T>> & p_Parameter = {}, const Condition &p_Condition = Condition::Default, const T &p_Value = 0)
	{
		parameter = p_Parameter;
		condition = p_Condition;
		value = p_Value;
	}

	void SetParameter(std::shared_ptr<Parameter<T>> &p_Parameter) { parameter = p_Parameter; }
	void SetCondition(Condition p_Condition) { condition = p_Condition; }
	void SetValue(T p_Value) { value = p_Value; }

	std::shared_ptr<Parameter<T>> &GetParameter() { return parameter; }
	Condition GetCondition() { return condition; }
	T GetValue() { return value; }
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

	void AddBoolTransitionCondition(std::shared_ptr<TransitionCondition<bool>> &p_TransitionCondition);
	void AddIntTransitionCondition(std::shared_ptr<TransitionCondition<int>> &p_TransitionCondition);
	void AddFloatTransitionCondition(std::shared_ptr<TransitionCondition<float>> &p_TransitionCondition);

private:
	bool MeetCondition();
	bool MeetBoolCondition();
	bool MeetIntCondition();
	bool MeetFloatCondition();
};