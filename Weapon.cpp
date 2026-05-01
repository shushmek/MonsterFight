#include "Weapon.h"

Weapon::Weapon(const string& name, const Rarity& rarity, const int& damage, const int& min, const int& max, const int& move, const int& combo, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime)
    : _name(name), _rarity(rarity), _damage(damage), _minBet(min), _maxBet(max), _move(move), _combo(combo)
{
    _sWeapon = new Object(texture, rect, frameCount, Ycount, frameTime, animTime);
}

void Weapon::TakeDamage(Creature target, int damage)
{
}

int Weapon::getDamage()
{
    return _damage;
}

string Weapon::getName()
{
    return _name;
}

int Weapon::getMinBet()
{
    return _minBet;
}

int Weapon::getMaxBet()
{
    return _maxBet;
}

int Weapon::getMove()
{
    return _move;
}

int Weapon::getCombo()
{
    return _combo;
}

//Effects Weapon::getEffect()
//{
//    return _effect;
//}
