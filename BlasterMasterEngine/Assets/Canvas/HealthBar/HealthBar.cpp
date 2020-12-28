#include "d3dpch.h"
#include "HealthBar.h"
#include "Assets/CharacterController.h"
#include "Assets/Characters/PlayerHealth.h"
#include "HealthBlock.h"
#include "Core/Canvas/UIElement/TextUI.h"

HealthBar::HealthBar(float x, float y)
	: UIElement(x, y)
{
	name = "Health Bar";
	spriteRenderer->enable = false;
}

void HealthBar::Start()
{
}

void HealthBar::Update()
{
	int lostHealth = 0;
	if (CharacterController::GetCharacterInControl() == Character::Sophia)
	{
		lostHealth = PlayerHealth::GetMaxHealth() - PlayerHealth::GetSophiaHealth();
		
	}
	else
	{
		lostHealth = PlayerHealth::GetMaxHealth() - PlayerHealth::GetJasonHealth();
	}

	int index = 0;
	for (index; index < lostHealth; ++index)
	{
		std::shared_ptr<HealthBlock> healthBlock = std::dynamic_pointer_cast<HealthBlock>(healthBlocks[index]);
		healthBlock->SetBlockState(false);
	}
	for (index; index < PlayerHealth::GetMaxHealth(); ++index)
	{
		std::shared_ptr<HealthBlock> healthBlock = std::dynamic_pointer_cast<HealthBlock>(healthBlocks[index]);
		healthBlock->SetBlockState(true);
	}
}

void HealthBar::CreateResources()
{
	float xPos = position.x;
	float yPos = position.y;

	healthBlocks[0] = std::make_shared<HealthBlock>(xPos, yPos - 59);
	healthBlocks[0]->SetName("Health Block 0");
	healthBlocks[0]->CreateResources();
	AddChildUIElement(healthBlocks[0]);

	healthBlocks[1] = std::make_shared<HealthBlock>(xPos, yPos - 42);
	healthBlocks[1]->SetName("Health Block 1");
	healthBlocks[1]->CreateResources();
	AddChildUIElement(healthBlocks[1]);

	healthBlocks[2] = std::make_shared<HealthBlock>(xPos, yPos - 25);
	healthBlocks[2]->SetName("Health Block 2");
	healthBlocks[2]->CreateResources();
	AddChildUIElement(healthBlocks[2]);

	healthBlocks[3] = std::make_shared<HealthBlock>(xPos, yPos - 8);
	healthBlocks[3]->SetName("Health Block 3");
	healthBlocks[3]->CreateResources();
	AddChildUIElement(healthBlocks[3]);

	healthBlocks[4] = std::make_shared<HealthBlock>(xPos, yPos + 8);
	healthBlocks[4]->SetName("Health Block 4");
	healthBlocks[4]->CreateResources();
	AddChildUIElement(healthBlocks[4]);

	healthBlocks[5] = std::make_shared<HealthBlock>(xPos, yPos + 25);
	healthBlocks[5]->SetName("Health Block 5");
	healthBlocks[5]->CreateResources();
	AddChildUIElement(healthBlocks[5]);

	healthBlocks[6] = std::make_shared<HealthBlock>(xPos, yPos + 42);
	healthBlocks[6]->SetName("Health Block 6");
	healthBlocks[6]->CreateResources();
	AddChildUIElement(healthBlocks[6]);

	healthBlocks[7] = std::make_shared<HealthBlock>(xPos, yPos + 59);
	healthBlocks[7]->SetName("Health Block 7");
	healthBlocks[7]->CreateResources();
	AddChildUIElement(healthBlocks[7]);

	std::shared_ptr<UIElement> healthBarText = std::make_shared<TextUI>(xPos, yPos + 115, "POW", "Health Bar Font");
	std::shared_ptr<TextUI> hpbText = std::dynamic_pointer_cast<TextUI>(healthBarText);
	if (hpbText != NULL)
	{
		hpbText->SetHorizontal(false);
	}
	healthBarText->CreateResources();
	AddChildUIElement(healthBarText);
}