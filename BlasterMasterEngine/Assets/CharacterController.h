#pragma once
enum class Character
{
	Sophia,
	Jason
};

class CharacterController
{
private:
	static Character character;
public:
	CharacterController() = default;
	CharacterController(const CharacterController& p_CharacterController) = delete;
	CharacterController& operator=(const CharacterController& p_CharacterController) = delete;

	static void SetCharacterInControl(Character p_Character);
	static Character GetCharacterInControl();
};