#include "Enemy.h"

Enemy::Enemy(const string& name, const int& lvl, const int& hp, const int& dmg, const int& arm, const int& move, const int& crit, const float& critMod, const int& minBet, const int& maxBet, Weapon& weapon, Armor& armor, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime)
	:_minBet(minBet), _maxBet(maxBet), Creature(name, lvl, hp, dmg, arm, move, crit, critMod, weapon, armor, texture, rect, frameCount, Ycount, frameTime, animTime) 
{
	this->setScale({-1, 1});
}

int Enemy::Bet()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(_minBet, _maxBet);
	return dist(gen);
}
