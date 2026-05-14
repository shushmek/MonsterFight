#pragma once
#include "Creature.h"
class Player:public Creature
{
public:
	Player(const string& name, const int& lvl, const int& hp, const int& dmg, const int& arm, const int& move, const int& crit, const float& critMod, const int& minBet, const int& maxBet, const int& cash, int maxCombo ,Weapon& weapon, Armor& armor,Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime = 0, float animTime = 0);
	int getMinBet();
	void setMinBet(int minBet);
	int getMaxBet();
	void setMaxBet(int maxBet);
	int getCash();
	void setCash(int cash);
	int getMaxCombo();
	void setMaxCombo(int  maxCombo);
	int getCombo();
	void setCombo(int combo);
	void LevelUp();

private:
	int _minBet;
	int _maxBet;
	int _cash;
	int _combo;
	int _maxCombo;
};

