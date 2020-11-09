#pragma once
#include "Animation.h"
#include "Transition.h"

class AnimationController
{
public:
	AnimationController();

	void AddAnimation(std::shared_ptr<Animation> animation);
	std::shared_ptr<Animation> GetCurrentAnimation();

	void SetBool(std::wstring p_Name, bool value);
	void SetInt(std::wstring p_Name, int value);
	void SetFloat(std::wstring p_Name, float value);

	bool GetBool(std::wstring p_Name);
	int GetInt(std::wstring p_Name);
	float GetFloat(std::wstring p_Name);

	int GetAnimationIndex(std::shared_ptr<Animation> animation);
	void SetDefaultAnimation(std::shared_ptr<Animation> p_Animation);
	void AddTransition(std::shared_ptr<Transition> p_Transition);
	void Update();

	void AddBoolParameter(std::shared_ptr<Parameter<bool>> parameter);
	void AddIntParameter(std::shared_ptr<Parameter<int>> parameter);
	void AddFloatParameter(std::shared_ptr<Parameter<float>> parameter);

private:
	void PlayCurrentAnimation();
	void CheckTransition();

private:
	std::vector<std::shared_ptr<Animation>> animations;
	std::vector<std::shared_ptr<Transition>> transitions;

	std::vector<std::shared_ptr<Parameter<bool>>> boolParameters;
	std::vector<std::shared_ptr<Parameter<int>>> intParameters;
	std::vector<std::shared_ptr<Parameter<float>>> floatParameters;

	int currentAnimationIndex;
};