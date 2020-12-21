#include "d3dpch.h"
#include "CharacterController.h"

Character CharacterController::character = Character::Sophia;

void CharacterController::SetCharacterInControl(Character p_Character)
{
	character = p_Character;
}

Character CharacterController::GetCharacterInControl()
{
	return character;
}
