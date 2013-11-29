#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Frame.h"
#include "Color.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "MultiMenu.h"
#include "Tween.h"
#include "Input.h"
#include "Character.h"
#include "BranchManager.h"
#include "Branch.h"
#include "PlayerStats.h"
#include "PlayerInventory.h"

PlayerInventory::PlayerInventory(BranchManager* bm, float x, float y)
{
	Branch::Branch(bm);
	manager = bm;
	timer.reset();
	frame = new Frame("inventory.fram", x, y);
	init(false);
}

PlayerInventory::PlayerInventory(BranchManager* bm)
{
	Branch::Branch(bm);
	manager = bm;
	timer.reset();
	frame = new Frame("inventory.fram", 10, -20);
	init(true);
}

PlayerInventory::~PlayerInventory()
{
}

void PlayerInventory::init(bool animate)
{
	//PLAYER INFO
	Text* name = new Text(false, Character::player->getName(), false, 0, 0, 
		frame->getPosition().x + 2, frame->getPosition().y + 2);

	//EQUIPMENT
	Text* message = new Text(false, "", false, 0, 0, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 0, 0, true, false, 3);
	cursor->play();
	Text* eq1 = new Text(false, Character::player->getInventory().getItem(0).getName(), false, 0, 0, 0, 0);
	items = new Menu(message, cursor, eq1, frame->getPosition().x + 23, frame->getPosition().y + 7, 72, 80);
	for (unsigned int i = 1; i < Character::player->getInventory().getSize(); i++)
	{
		Text* eqi = new Text(false, Character::player->getInventory().getItem(i).getName(), false, 0, 0, 0, i);
		items->addMember(eqi);
	}

	//Equipment
	selected = Character::player->getInventory().getItem(items->getFocusedIndex());
	if (selected.getItemType() == Weapon)
	{
		selectedName = new Text(false, Character::player->getWeapon().getName(), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 6);
		selectedStr = new Text(false, "Melee: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().melee)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 7);
		selectedDex = new Text(false, "Ranged: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().range)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 8);
		selectedInt = new Text(false, "Magic: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().magic)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 9);

		currentName = new Text(false, selected.getName(), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 13);
		currentStr = new Text(false, "Melee: " + to_string(static_cast<long long>(selected.getStats().melee)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 14);
		currentDex = new Text(false, "Ranged: " + to_string(static_cast<long long>(selected.getStats().range)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 15);
		currentInt = new Text(false, "Magic: " + to_string(static_cast<long long>(selected.getStats().magic)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 16);
	}
	else
	{
		selectedName = new Text(false, Character::player->getArmor().getName(), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 6);
		selectedStr = new Text(false, "Armor: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().armor)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 7);
		selectedDex = new Text(false, "Dodge: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().dodge)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 8);
		selectedInt = new Text(false, "Resist: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().resist)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 9);

		currentName = new Text(false, selected.getName(), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 13);
		currentStr = new Text(false, "Armor: " + to_string(static_cast<long long>(selected.getStats().armor)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 14);
		currentDex = new Text(false, "Dodge: " + to_string(static_cast<long long>(selected.getStats().dodge)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 15);
		currentInt = new Text(false, "Resist: " + to_string(static_cast<long long>(selected.getStats().resist)), 
			false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 16);
	}

	//USABLES
	Text* hpPot = new Text(false, to_string(static_cast<long long>(Character::player->getUsables().hpPotions))
		+ " HP Potions", true, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 7);
	Text* strPot = new Text(false, to_string(static_cast<long long>(Character::player->getUsables().strPotions))
		+ " STR Potions", true, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 9);
	Text* dexPot = new Text(false, to_string(static_cast<long long>(Character::player->getUsables().dexPotions))
		+ " DEX Potions", true, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 11);
	Text* intPot = new Text(false, to_string(static_cast<long long>(Character::player->getUsables().intPotions))
		+ " INT Potions", true, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 13);

	//GOLD
	Text* gold = new Text(false, to_string(static_cast<long long>(Character::player->getGold().gold)) + "g", 
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 16);
	gold->setForegroundColor(FG_YELLOW);
	Text* silver= new Text(false, to_string(static_cast<long long>(Character::player->getGold().silver)) + "s", 
		false, 0, 0, frame->getPosition().x + 46, frame->getPosition().y + 16);
	silver->setForegroundColor(FG_WHITE);
	Text* copper= new Text(false, to_string(static_cast<long long>(Character::player->getGold().copper)) + "c", 
		false, 0, 0, frame->getPosition().x + 50, frame->getPosition().y + 16);
	copper->setForegroundColor(FG_RED);

	Tween* tween = new Tween(SinOut, frame, 10, 3, 0.3f);
	tween->add(name);
	tween->add(items);
	tween->add(currentName);
	tween->add(currentStr);
	tween->add(currentDex);
	tween->add(currentInt);
	tween->add(selectedName);
	tween->add(selectedStr);
	tween->add(selectedDex);
	tween->add(selectedInt);
	tween->add(hpPot);
	tween->add(strPot);
	tween->add(dexPot);
	tween->add(intPot);
	tween->add(gold);
	tween->add(silver);
	tween->add(copper);
	tween->play();

	myFrames.push_back(frame);
	myFrames.push_back(items);
	myFrames.push_back(name);
	myFrames.push_back(currentName);
	myFrames.push_back(currentStr);
	myFrames.push_back(currentDex);
	myFrames.push_back(currentInt);
	myFrames.push_back(selectedName);
	myFrames.push_back(selectedStr);
	myFrames.push_back(selectedDex);
	myFrames.push_back(selectedInt);
	myFrames.push_back(hpPot);
	myFrames.push_back(strPot);
	myFrames.push_back(dexPot);
	myFrames.push_back(intPot);
	myFrames.push_back(gold);
	myFrames.push_back(silver);
	myFrames.push_back(copper);

	myTweens.push_back(tween);
}

void PlayerInventory::update(float delta)
{
	Branch::update(delta);

	for (unsigned int i = 0; i < myTweens.size(); i++)
	{
		myTweens.at(i)->update();
	}
	for (unsigned int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->update(delta);
	}
}

void PlayerInventory::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}
void PlayerInventory::start(float delta)
{
	if (Input::keyHit() && (Input::get() == 'i' || Input::get() == 'b'))
	{
		state = End;
		myTweens.at(0)->restart(10, -22);
		myTweens.at(0)->setDuration(0.3f);
	}
	else if (Input::get() == 's' || Input::get() == 'p')
	{
		manager->swap(new PlayerStats(manager, frame->getPosition().x, frame->getPosition().y));
	}

	selected = Character::player->getInventory().getItem(items->getFocusedIndex());
	if (selected.getItemType() == Weapon)
	{
		currentName->setText(false, Character::player->getWeapon().getName());
		currentStr->setText(false, "Melee: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().melee)));
		currentDex->setText(false, "Range: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().range)));
		currentInt->setText(false, "Magic: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().magic)));

		selectedName->setText(false, selected.getName());
		selectedStr->setText(false, "Melee: " + to_string(static_cast<long long>(selected.getStats().melee)));
		selectedDex->setText(false, "Range: " + to_string(static_cast<long long>(selected.getStats().range)));
		selectedInt->setText(false, "Magic: " + to_string(static_cast<long long>(selected.getStats().magic)));
	}
	else
	{
		currentName->setText(false, Character::player->getArmor().getName());
		currentStr->setText(false, "Armor: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().armor)));
		currentDex->setText(false, "Dodge: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().dodge)));
		currentInt->setText(false, "Resist: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().resist)));

		selectedName->setText(false, selected.getName());
		selectedStr->setText(false, "Armor: " + to_string(static_cast<long long>(selected.getStats().armor)));
		selectedDex->setText(false, "Dodge: " + to_string(static_cast<long long>(selected.getStats().dodge)));
		selectedInt->setText(false, "Resist: " + to_string(static_cast<long long>(selected.getStats().resist)));
	}

	items->input();
	if (Input::keyHit() && Input::get() == 13)
	{
		Character::player->equip(selected);
	}
}

void PlayerInventory::input(float delta)
{
}

void PlayerInventory::end(float delta)
{
	if (Input::keyHit() && (Input::get() == 'i' || Input::get() == 'b'))
	{
		state = Start;
		myTweens.at(0)->restart(10, 3);
	}

	if (myTweens.at(0)->isFinished())
	{
		Input::clear();
		manager->setInMenu(false);
		manager->pop();
	}
}