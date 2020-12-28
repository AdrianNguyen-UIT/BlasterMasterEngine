#pragma once

class PlayerHealth
{
private:
	static int sophiaHealth;
	static int jasonHealth;
	static int maxHealth;
	static int life;
	static int maxLife;
public:
	PlayerHealth() = default;
	PlayerHealth(const PlayerHealth& p_PlayerHealth) = delete;
	PlayerHealth& operator=(const PlayerHealth& p_PlayerHealth) = delete;

	static int GetSophiaHealth();
	static int GetJasonHealth();
	static void SetSophiaHealth(const int &health);
	static void SetJasonHealth(const int &health);
	static void ResetHealth();
	static void ResetLife();
	static int GetMaxHealth() { return maxHealth; }
	static int GetPlayerLife();
	static void SetPlayerLife(const int& l);
};