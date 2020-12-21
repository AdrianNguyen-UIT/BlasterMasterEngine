#pragma once
#include "Animation.h"
#include "Transition.h"

class AnimationController
{
public:
	bool forward;
	bool enable;
public:
	AnimationController();

	void AddAnimation(std::shared_ptr<Animation> &animation);
	std::shared_ptr<Animation> &GetCurrentAnimation();

	void SetBool(std::string p_Name, bool value);
	void SetInt(std::string p_Name, int value);
	void SetFloat(std::string p_Name, float value);

	bool GetBool(std::string p_Name);
	int GetInt(std::string p_Name);
	float GetFloat(std::string p_Name);

	int GetAnimationIndex(std::shared_ptr<Animation> &p_Animation);
	void SetDefaultAnimation(std::shared_ptr<Animation> &p_Animation);
	void AddTransition(std::shared_ptr<Transition> &p_Transition);
	void Update();

	void AddBoolParameter(std::shared_ptr<Parameter<bool>> &parameter);
	void AddIntParameter(std::shared_ptr<Parameter<int>> &parameter);
	void AddFloatParameter(std::shared_ptr<Parameter<float>> &parameter);

	void PauseAnimation();
	void PlayAnimation(bool p_Forward = true);
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
	bool playCurrentAnimation;
};