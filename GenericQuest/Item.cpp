#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	name = "NULL";
	type = Weapon;
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

Item::Item(string myName, ItemType myType, int newStr, int newDex, int newInt)
{
	name = myName;
	type = myType;
	stats.health = 0;
	stats.strength = 0;
	stats.dexterity = 0;
	stats.intelligence = 0;
	
	if (type == Weapon)
	{
		stats.melee = newStr;
		stats.range = newDex;
		stats.magic = newInt;
		stats.armor = 0;
		stats.dodge = 0;
		stats.resist = 0;
	}
	else if (type == Armor)
	{
		stats.armor = newStr;
		stats.dodge = newDex;
		stats.resist = newInt;
		stats.melee = 0;
		stats.range = 0;
		stats.magic = 0;
	}
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