#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	name = "NULL";
	stats.health = 0;
	stats.strength = 0;
	stats.dexterity = 0;
	stats.intelligence = 0;
	stats.armor = 0;
	stats.dodge = 0;
	stats.resist = 0;
	stats.melee = 0;
	stats.range = 0;
	stats.magic = 0;
}

Item::Item(string myName, ItemType myType, 
		int newHealth, int newStr, int newDex, int newInt, 
		int newArmor, int newDodge, int newResist, 
		int newMelee, int newRange, int newMagic)
{
	name = myName;
	stats.health = newHealth;
	stats.strength = newStr;
	stats.dexterity = newDex;
	stats.intelligence = newInt;
	stats.armor = newArmor;
	stats.dodge = newDodge;
	stats.resist = newResist;
	stats.melee = newMelee;
	stats.range = newRange;
	stats.magic = newMagic;
}

Item::~Item()
{
}

void Item::setName(string myName)
{
	name = myName;
}

string Item::getName()
{
	return name;
}

Stats Item::getStats()
{
	return stats;
}

ItemType Item::getItemType()
{
	return type;
}