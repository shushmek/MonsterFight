#pragma once
#include "Creature.h"
#include <random>
class Enemy:public Creature
{
public:
	Enemy(const string& name, const int& lvl, const int& hp, const int& dmg, const int& arm, const int& move, const int& crit, const float& critMod, const int& minBet, const int& maxBet, Weapon& weapon, Armor& armor, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime = 0, float animTime = 0);
	int Bet();
private:
	int _minBet;
	int _maxBet;
};

