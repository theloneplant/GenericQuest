#include "stdafx.h"
#include "Item.h"
#include "Inventory.h"

Inventory::Inventory() : SIZE (10)
{
	
}

Inventory::~Inventory()
{
}

bool Inventory::add(Item newItem)
{
	if (items.size() < SIZE)
	{
		items.push_back(newItem);
		return true;
	}
	else
		return false;
}

bool Inventory::remove(string itemName)
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (items.at(i).getName() == itemName)
		{
			items.erase(items.begin() + i);
			return true;
		}
	}

	return false;
}

void Inventory::clear()
{
	while (items.size() > 0)
	{
		items.pop_back();
	}
}

Item Inventory::getItem(unsigned int i)
{
	if (i < items.size())
		return items.at(i);

	Item temp;
	return temp;
}

Item Inventory::getItem(string name)
{
	for (unsigned int i = 0; i < items.size(); i++)
	{
		if (items.at(i).getName() == name)
			return items.at(i);
	}
	Item temp;
	return temp;
}

int Inventory::getSize()
{
	return items.size();
}