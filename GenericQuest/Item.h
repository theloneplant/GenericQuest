#ifndef ITEM
#define ITEM

enum ItemType
{
	Armor, Weapon
};

struct Stats
{
	int health, strength, dexterity, intelligence,
		armor, dodge, resist, melee, range, magic;
};

class Item
{
    public:
		Item();
		Item(string myName, ItemType myType, int newStr, int newDex, int newInt);
		~Item();
		void setName(string myName);
		void setStats(Stats newStats);
		void setItemType(ItemType newItemType);
		string getName();
		Stats getStats();
		ItemType getItemType();

	private:
		string name;
		Stats stats;
		ItemType type;
};
#endif