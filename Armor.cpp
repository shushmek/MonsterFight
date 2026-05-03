#include "Armor.h"

Armor::Armor(const string& name, const Rarity& rarity, const int& armor, const int& min, const int& max, const int& move, const int& combo, const int& crit, const float& critMode, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime)
    : _name(name), _rarity(rarity), _armor(armor), _minBet(min), _maxBet(max), _move(move), _combo(combo), _critChace(crit), _critMod(critMode)
{
    _sArmor = new Object(texture, rect, frameCount, Ycount, frameTime, animTime);
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
void Armor::setPosition(Vector2f pos)
{
    _sArmor->setPosition(pos);
}
void Armor::setScale(Vector2f scale)
{
    _sArmor->setScale(scale);
}

void Armor::draw(RenderWindow& window) const
{
    _sArmor->draw(window);
}

void Armor::AnimPlay()
{
	_sArmor->AnimPlay();
}

void Armor::AnimPause()
{
	_sArmor->AnimPause();
}

bool Armor::AnimGetPlay()
{
	return _sArmor->AnimGetPlay();
}

void Armor::AnimSetLoop(bool loop)
{
	_sArmor->AnimSetLoop(loop);
}

void Armor::AnimSetFrameTime(int frametime)
{
	_sArmor->AnimSetFrameTime(frametime);
}

void Armor::AminSetAnimTime(float animTime)
{
	_sArmor->AminSetAnimTime(animTime);
}

void Armor::AnimReset()
{
	_sArmor->AnimReset();
}

bool Armor::AnimIsFinished() const
{
	return _sArmor->AnimIsFinished();
}

void Armor::AnimSetOnFinished(function<void()> callback)
{
	_sArmor->AnimSetOnFinished(callback);
}

void Armor::AnimUpdate(Time dt)
{
	_sArmor->AnimUpdate(dt);
}

void Armor::AnimStop()
{
	_sArmor->AnimStop();
}
