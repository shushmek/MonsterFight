#pragma once
#include "Armor.h"
#include "Weapon.h"
#include "Creature.h"
#include "Player.h"
#include "Enemy.h"




class ItemList
{
public:
    Action* actions = new Action[]{
        Action("Default")   //0
    };
    Weapon* weapons = new Weapon[]{
        Weapon("None", Weapon::None, 0 ,0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Sword.png"), IntRect({ 0,0 }, { 1,1 }), 1, 1, 100),             //0
        Weapon("Sword", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Sword.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100)      //1
    };
    Armor* armors = new Armor[]{
        Armor("None", Armor::None, 0 ,0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Sword.png"), IntRect({ 0,0 }, { 1,1 }), 1, 1, 100),               //0
        Armor("Halmet", Armor::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Halmet.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100)      //1
    };  
    //Enemy* enemys = new Enemy[]{
    //    Enemy("Goblin", 1, 100, 1, 0, 3, 0, 2.f, 2, 6, weapons[0], armors[1], AssetManager::GetTexture("Sprite/Goblin.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100)
    //
    //};
};
