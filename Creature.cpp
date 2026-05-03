#include "Creature.h"


Creature::Creature(const string& name, const int& lvl, const int& hp, const int& dmg, const int& arm, const int& move, const int& crit, const float& critMod, Weapon& weapon, Armor& armor,  Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime, float animTime)
	:_name(name), _level(lvl), _health(hp), _damage(dmg), _arm(arm), _move(move), _critChance(crit), _critMod(critMod), _weapon(&weapon), _armor(&armor), _maxHP(hp), _maxMove(move)
{
	 _sprite = new Object(texture, rect, frameCount, Ycount, frameTime, animTime);
}

void Creature::draw(RenderWindow& win) const
{
	_sprite->draw(win);
	_armor->draw(win);
	_weapon->draw(win);
}

void Creature::setPosition(Vector2f pos)
{
	_weapon->setPosition(pos);
	_armor->setPosition(pos);
	_sprite->setPosition(pos);
}

Vector2f Creature::getPosition()
{
	return _sprite->getPosition();
}

void Creature::setScale(Vector2f scale)
{
	_weapon->setScale(scale);
	_armor->setScale(scale);
	_sprite->setScale(scale);
}

Vector2f Creature::getScale()
{
	return _sprite->getScale();
}

string Creature::getName()
{
	return _name;
}

int Creature::getLevel()
{
	return _level;
}

int Creature::getMaxHealth()
{
	return _maxHP;
}

int Creature::getHealth()
{
	return _health;
}

int Creature::getDamage()
{
	return _damage;
}

int Creature::getArm()
{
	return _arm;
}

int Creature::getMaxMove()
{
	return _maxMove;
}

int Creature::getMove()
{
	return _move;
}

int Creature::getCritChance()
{
	return _critChance;
}

float Creature::getCritMod()
{
	return _critMod;
}

Weapon Creature::getWeapon()
{
	return *_weapon;
}

Armor Creature::getArmor()
{
	return *_armor;
}

void Creature::setName(string name)
{
	_name = name;
}

void Creature::setLevel(int lvl)
{
	_level = lvl;
}

void Creature::setMaxHealth(int maxHP)
{
	_maxHP = maxHP;
}

void Creature::setHealth(int hp)
{
	_health = hp;
}

void Creature::setDamage(int dmg)
{
	_damage = dmg;
}

void Creature::setArm(int arm)
{
	_arm = arm;
}

void Creature::setMaxMove(int maxMove)
{
	_maxMove = maxMove;
}

void Creature::setMove(int move)
{
	_move = move;
}

void Creature::setCritChance(int critChance)
{
	_critChance = critChance;
}

void Creature::setCritMod(float critMod)
{
	_critMod = critMod;
}

void Creature::setWeapon(Weapon weapon)
{
	*_weapon = weapon;
}

void Creature::setArmor(Armor armor)
{
	*_armor = armor;
}

void Creature::TakeDamage(int damage)
{
	_health -= damage;
}


void Creature::AnimPlay()
{
	_weapon->AnimPlay();
	_armor->AnimPlay();
	_sprite->AnimPlay();
}

void Creature::AnimPause()
{
	_weapon->AnimPause();
	_armor->AnimPause();
	_sprite->AnimPause();
}

bool Creature::AnimGetPlay()
{
	return _sprite->AnimGetPlay();
}

void Creature::AnimSetLoop(bool loop)
{
	_weapon->AnimSetLoop(loop);
	_armor->AnimSetLoop(loop);
	_sprite->AnimSetLoop(loop);
}

void Creature::AnimSetFrameTime(int frametime)
{
	_weapon->AnimSetFrameTime(frametime);
	_armor->AnimSetFrameTime(frametime);
	_sprite->AnimSetFrameTime(frametime);
}

void Creature::AminSetAnimTime(float animTime)
{
	_weapon->AminSetAnimTime(animTime);
	_armor->AminSetAnimTime(animTime);
	_sprite->AminSetAnimTime(animTime);
}

void Creature::AnimReset()
{
	_weapon->AnimReset();
	_armor->AnimReset();
	_sprite->AnimReset();
}

bool Creature::AnimIsFinished() const
{
	return _sprite->AnimIsFinished();
}

void Creature::AnimSetOnFinished(function<void()> callback)
{
	_sprite->AnimSetOnFinished(callback);
}

void Creature::AnimUpdate(Time dt)
{
	_weapon->AnimUpdate(dt);
	_armor->AnimUpdate(dt);
	_sprite->AnimUpdate(dt);
}

void Creature::AnimStop()
{
	_weapon->AnimStop();
	_armor->AnimStop();
	_sprite->AnimStop();
}