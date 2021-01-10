#include "d3dpch.h"
#include "CreditPanel.h"

CreditPanel::CreditPanel(const float x, const float y)
	: UIElement(x, y)
{
	spriteRenderer->enable = false;
}

void CreditPanel::Update()
{
	int count = 0;

	for (size_t index = 0; index < 23; ++index)
	{
		if (childUIElements[index]->GetPosition().y > (position.y - 700.0f))
		{
			childUIElements[index]->SetPosition(childUIElements[index]->GetPosition().x,
				childUIElements[index]->GetPosition().y - 1.0f, 0.0f);
		}
		else
		{
			++count;
		}
	}

	if (count == 23)
	{
		childUIElements[23]->SetEnable(true);
		childUIElements[24]->SetEnable(true);
	}
}

void CreditPanel::CreateResources()
{
	float initY = position.y + 400.0f;

	childUIElements.reserve(25);
	{
		std::shared_ptr<UIElement> director = std::make_shared<TextUI>(position.x + 30.0f, initY, "DIRECTOR", "Ending Font");
		director->CreateResources();
		childUIElements.emplace_back(director);

		std::shared_ptr<UIElement> director1 = std::make_shared<TextUI>(position.x + 158.0f, initY + 40.0f, "H.HIGASIYA", "Ending Font");
		director1->CreateResources();
		childUIElements.emplace_back(director1);

		std::shared_ptr<UIElement> director2 = std::make_shared<TextUI>(position.x + 158.0f, initY + 80.0f, "K.KITAZUMI", "Ending Font");
		director2->CreateResources();
		childUIElements.emplace_back(director2);
	}

	{
		std::shared_ptr<UIElement> manager = std::make_shared<TextUI>(position.x + 20.0f, initY + 140.0f, "MANAGER", "Ending Font");
		manager->CreateResources();
		childUIElements.emplace_back(manager);

		std::shared_ptr<UIElement> manager1 = std::make_shared<TextUI>(position.x + 148.0f, initY + 180.0f, "K.YOSHIDA", "Ending Font");
		manager1->CreateResources();
		childUIElements.emplace_back(manager1);
	}

	{
		std::shared_ptr<UIElement> gameDesign = std::make_shared<TextUI>(position.x + 70.0f, initY + 240.0f, "GAME DESIGN", "Ending Font");
		gameDesign->CreateResources();
		childUIElements.emplace_back(gameDesign);

		std::shared_ptr<UIElement> gameDesign1 = std::make_shared<TextUI>(position.x + 113.0f, initY + 280.0f, "FANKY.", "Ending Font");
		gameDesign1->CreateResources();
		childUIElements.emplace_back(gameDesign1);

		std::shared_ptr<UIElement> gameDesign2 = std::make_shared<TextUI>(position.x + 163.0f, initY + 320.0f, "AND OTHERS", "Ending Font");
		gameDesign2->CreateResources();
		childUIElements.emplace_back(gameDesign2);
	}

	{
		std::shared_ptr<UIElement> characterDesign = std::make_shared<TextUI>(position.x + 130.0f, initY + 380.0f, "CHARACTER DESIGN", "Ending Font");
		characterDesign->CreateResources();
		childUIElements.emplace_back(characterDesign);

		std::shared_ptr<UIElement> characterDesign1 = std::make_shared<TextUI>(position.x + 113.0f, initY + 420.0f, "FANKY.", "Ending Font");
		characterDesign1->CreateResources();
		childUIElements.emplace_back(characterDesign1);
	}

	{
		std::shared_ptr<UIElement> artDesign = std::make_shared<TextUI>(position.x + 58.0f, initY + 480.0f, "ART DESIGN", "Ending Font");
		artDesign->CreateResources();
		childUIElements.emplace_back(artDesign);

		std::shared_ptr<UIElement> artDesign1 = std::make_shared<TextUI>(position.x + 125.0f, initY + 520.0f, "PGM F1.", "Ending Font");
		artDesign1->CreateResources();
		childUIElements.emplace_back(artDesign1);
	}

	{
		std::shared_ptr<UIElement> musicComposer = std::make_shared<TextUI>(position.x + 110.0f, initY + 580.0f, "MUSIC COMPOSER", "Ending Font");
		musicComposer->CreateResources();
		childUIElements.emplace_back(musicComposer);

		std::shared_ptr<UIElement> musicComposer1 = std::make_shared<TextUI>(position.x + 188.0f, initY + 620.0f, "NAOKI KODAKA", "Ending Font");
		musicComposer1->CreateResources();
		childUIElements.emplace_back(musicComposer1);
	}

	{
		std::shared_ptr<UIElement> soundProgram = std::make_shared<TextUI>(position.x + 97.0f, initY + 680.0f, "SOUND PROGRAM", "Ending Font");
		soundProgram->CreateResources();
		childUIElements.emplace_back(soundProgram);

		std::shared_ptr<UIElement> soundProgram1 = std::make_shared<TextUI>(position.x + 115.0f, initY + 720.0f, "MARUMO", "Ending Font");
		soundProgram1->CreateResources();
		childUIElements.emplace_back(soundProgram1);
	}

	{
		std::shared_ptr<UIElement> program = std::make_shared<TextUI>(position.x + 24.0f, initY + 780.0f, "PROGRAM", "Ending Font");
		program->CreateResources();
		childUIElements.emplace_back(program);

		std::shared_ptr<UIElement> program1 = std::make_shared<TextUI>(position.x + 100.0f, initY + 820.0f, "SENTA", "Ending Font");
		program1->CreateResources();
		childUIElements.emplace_back(program1);

		std::shared_ptr<UIElement> program2 = std::make_shared<TextUI>(position.x + 89.0f, initY + 860.0f, "KANZ", "Ending Font");
		program2->CreateResources();
		childUIElements.emplace_back(program2);
	}

	{
		std::shared_ptr<UIElement> special = std::make_shared<TextUI>(position.x + 27.0f, initY + 920.0f, "SPECIAL", "Ending Font");
		special->CreateResources();
		childUIElements.emplace_back(special);

		std::shared_ptr<UIElement> tksTo = std::make_shared<TextUI>(position.x + 80.0f, initY + 950.0f, "THANKS TO", "Ending Font");
		tksTo->CreateResources();
		childUIElements.emplace_back(tksTo);

		std::shared_ptr<UIElement> specialTks1 = std::make_shared<TextUI>(position.x + 126.0f, initY + 990.0f, "MORIKEN", "Ending Font");
		specialTks1->CreateResources();
		childUIElements.emplace_back(specialTks1);

		std::shared_ptr<UIElement> specialTks2 = std::make_shared<TextUI>(position.x + 101.0f, initY + 1030.0f, "CHIAO", "Ending Font");
		specialTks2->CreateResources();
		childUIElements.emplace_back(specialTks2);
	}

	{
		RECT rect = { 3, 62, 232, 243 };
		std::shared_ptr<UIElement> theEnd = std::make_shared<ImageUI>(position.x + 50.0f, position.y - 100.0f, "Badge_Texture", rect);
		theEnd->CreateResources();
		childUIElements.emplace_back(theEnd);

		std::shared_ptr<UIElement> veryTks = std::make_shared<TextUI>(position.x + 80.0f, position.y + 100.0f, "VERY THANKS..!!", "Ending Font");
		veryTks->CreateResources();
		childUIElements.emplace_back(veryTks);

		childUIElements[23]->SetEnable(false);
		childUIElements[24]->SetEnable(false);
	}
}