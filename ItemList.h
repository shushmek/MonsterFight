#pragma once
#include "Armor.h"
#include "Weapon.h"
#include "Creature.h"
#include "Player.h"
#include "Enemy.h"




class ItemList
{
public:
    ItemList();
    Weapon* weapons = new Weapon[]{
        Weapon("None", Weapon::None, 0 ,0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,0 }, { 1,1 }), 1, 1, 100),            //0     
        Weapon("Stick", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),    //1
        Weapon("Sai", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),    //2
        Weapon("Sword", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),    //3
        Weapon("Axe", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,768 }, { 256,256 }), 10, 1, 100),    //4
        Weapon("Shield", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,1024 }, { 256,256 }), 10, 1, 100),    //5
        Weapon("Spear", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,1280 }, { 256,256 }), 10, 1, 100),    //6
        Weapon("Saber", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,1536 }, { 256,256 }), 10, 1, 100),    //7
        Weapon("Fire staff", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,1792 }, { 256,256 }), 10, 1, 100),    //8
        Weapon("Baloon", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,2048 }, { 256,256 }), 10, 1, 100),    //9
        Weapon("Chain Sword", Weapon::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Weapon.png"), IntRect({ 0,2304 }, { 256,256 }), 10, 1, 100)     //10   
    };
    Armor* armors = new Armor[]{
        Armor("None", Armor::None, 0 ,0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,0 }, { 1,1 }), 1, 1, 100),                       //0
        Armor("Halmet", Armor::Common, 1, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),              //1
        Armor("Halmet+", Armor::Rare, 2, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),             //2
        Armor("Mask", Armor::Common, 1, 0,0,0,0,30,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),             //3
        Armor("ClownHat", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,768 }, { 256,256 }), 10, 1, 100),      //4
        Armor("Trash Lid", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,1024 }, { 256,256 }), 10, 1, 100),     //5
        Armor("Breastplate", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,1280 }, { 256,256 }), 10, 1, 100),     //6
        Armor("Jacket", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,1536 }, { 256,256 }), 10, 1, 100),     //7
        Armor("Bib", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,1792 }, { 256,256 }), 10, 1, 100),     //8
        Armor("Vagabond Set", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,2048 }, { 256,256 }), 10, 1, 100),     //9
        Armor("Knight Set", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,2304 }, { 256,256 }), 10, 1, 100),     //10
        Armor("Thief's Set", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,2560 }, { 256,256 }), 10, 1, 100),     //11
        Armor("Clown Set", Armor::Legendary, 10, 0,0,0,0,0,0.f, AssetManager::GetTexture("Sprite/Armor.png"), IntRect({ 0,2816 }, { 256,256 }), 10, 1, 100),     //12
    };
    

};

