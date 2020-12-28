#pragma once
#include "Core/FontResources/Font.h"

class HealthBarFont : public Font
{
public:
	HealthBarFont();

	virtual void CreateResources() override;
};