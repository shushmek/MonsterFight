#include "Armor.h"

Armor::Armor(const string& name, const Rarity& rarity, const int& armor, const int& min, const int& max, const int& move, const int& combo, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime)
    : _name(name), _rarity(rarity), _armor(armor), _minBet(min), _maxBet(max), _move(move), _combo(combo)
{
    _sArmor = new Object(texture, rect, frameCount, Ycount, frameTime, animTime);
}

void Armor::TakeDamage(Creature target, int damage)
{
}

int Armor::getArmor()
{
    return _armor;
}

string Armor::getName()
{
    return _name;
}

int Armor::getMinBet()
{
    return _minBet;
}

int Armor::getMaxBet()
{
    return _maxBet;
}

int Armor::getMove()
{
    return _move;
}

int Armor::getCombo()
{
    return _combo;
}