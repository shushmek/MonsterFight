#pragma once
#include "Armor.h"
#include "Weapon.h"

using namespace sf;
using namespace std;

class ItemList
{
public:
    Weapon* weapons = new Weapon[]{Weapon("Sword", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Sword.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100) };
    Armor* armors = new Armor[]{ Armor("Halmet", Armor::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Halmet.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100) };
};

