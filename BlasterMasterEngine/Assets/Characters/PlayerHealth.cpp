#include "d3dpch.h"
#include "PlayerHealth.h"


int PlayerHealth::jasonHealth = 8;
int PlayerHealth::sophiaHealth = 8;
int PlayerHealth::maxHealth = 8;
int PlayerHealth::life = 2;
int PlayerHealth::maxLife = 2;

int PlayerHealth::GetSophiaHealth()
{
	return sophiaHealth;
}

int PlayerHealth::GetJasonHealth()
{
	return jasonHealth;
}

void PlayerHealth::SetSophiaHealth(const int& health)
{
	sophiaHealth = health;
}

void PlayerHealth::SetJasonHealth(const int& health)
{
	jasonHealth = health;
}

void PlayerHealth::ResetHealth()
{
	jasonHealth = maxHealth;
	sophiaHealth = maxHealth;
}

void PlayerHealth::ResetLife()
{
	life = maxLife;
}

int PlayerHealth::GetPlayerLife()
{
	return life;
}

void PlayerHealth::SetPlayerLife(const int& l)
{
	life = l;
}
