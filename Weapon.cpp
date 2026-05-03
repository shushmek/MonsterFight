#include "Weapon.h"

Weapon::Weapon(const string& name, const Rarity& rarity, const int& damage, const int& min, const int& max, const int& move, const int& combo, const int& crit, const float& critMode, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime)
    : _name(name), _rarity(rarity), _damage(damage), _minBet(min), _maxBet(max), _move(move), _combo(combo), _critChace(crit), _critMod(critMode)
{
    _sWeapon = new Object(texture, rect, frameCount, Ycount, frameTime, animTime);
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

void Weapon::setPosition(Vector2f pos)
{
    _sWeapon->setPosition(pos);
}

void Weapon::setScale(Vector2f scale)
{
    _sWeapon->setScale(scale);
}

void Weapon::draw(RenderWindow& window) const
{
    _sWeapon->draw(window);
}

void Weapon::AnimPlay()
{
	_sWeapon->AnimPlay();
}

void Weapon::AnimPause()
{
	_sWeapon->AnimPause();
}

bool Weapon::AnimGetPlay()
{
	return _sWeapon->AnimGetPlay();
}

void Weapon::AnimSetLoop(bool loop)
{
	_sWeapon->AnimSetLoop(loop);
}

void Weapon::AnimSetFrameTime(int frametime)
{
	_sWeapon->AnimSetFrameTime(frametime);
}

void Weapon::AminSetAnimTime(float animTime)
{
	_sWeapon->AminSetAnimTime(animTime);
}

void Weapon::AnimReset()
{
	_sWeapon->AnimReset();
}

bool Weapon::AnimIsFinished() const
{
	return _sWeapon->AnimIsFinished();
}

void Weapon::AnimSetOnFinished(function<void()> callback)
{
	_sWeapon->AnimSetOnFinished(callback);
}

void Weapon::AnimUpdate(Time dt)
{
	_sWeapon->AnimUpdate(dt);
}

void Weapon::AnimStop()
{
	_sWeapon->AnimStop();
}