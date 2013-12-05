#ifndef INVENTORY
#define INVENTORY

class Item;

class Inventory
{
    public:
		Inventory();
		~Inventory();
		bool add(Item newItem);
		bool remove(string itemName);
		void clear();
		Item getItem(unsigned int index);
		Item getItem(string name);
		int getSize();

	private:
		const unsigned int SIZE;
		vector<Item> items;
};
#endif