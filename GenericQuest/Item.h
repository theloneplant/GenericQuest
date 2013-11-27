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
		Item(string myName, ItemType myType, 
			int newHealth, int newStr, int newDex, int newInt, 
			int newArmor, int newDodge, int newResist, 
			int newMelee, int newRange, int newMagic);
		~Item();
		void setName(string myName);
		string getName();
		Stats getStats();
		ItemType getItemType();

	private:
		string name;
		Stats stats;
		ItemType type;
};
#endif