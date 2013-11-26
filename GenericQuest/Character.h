#ifndef CHARACTER
#define CHARACTER



class Character
{
	public:
		Character();
		~Character();
		virtual void attack(Character enemy);
		virtual void addItem();
		virtual void removeItem();

	private:
		int health, strength, dexterity, intelligence;
		string name;
};

#endif