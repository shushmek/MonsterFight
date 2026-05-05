#include "Player.h"

Player::Player(const string& name, const int& lvl, const int& hp, const int& dmg, const int& arm, const int& move, const int& crit, const float& critMod, const int& minBet, const int& maxBet, const int& cash, Weapon& weapon, Armor& armor, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime)
	:_minBet(minBet), _maxBet(maxBet), _cash(cash), Creature(name, lvl, hp, dmg, arm, move, crit, critMod, weapon, armor, texture, rect, frameCount, Ycount, frameTime, animTime){}

int Player::getMinBet()
{
	return _minBet;
}

void Player::setMinBet(int minBet)
{
	_minBet = minBet;
}

int Player::getMaxBet()
{
	return _maxBet;
}

void Player::setMaxBet(int maxBet)
{
	_maxBet = maxBet;
}

int Player::getCash()
{
	return _cash;
}

void Player::setCash(int cash)
{
	_cash = cash;
}
