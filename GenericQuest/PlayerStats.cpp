#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Frame.h"
#include "Color.h"
#include "Text.h"
#include "Animation.h"
#include "StatusBar.h"
#include "Menu.h"
#include "Tween.h"
#include "Input.h"
#include "Random.h"
#include "Character.h"
#include "BranchManager.h"
#include "Branch.h"
#include "PlayerInventory.h"
#include "PlayerStats.h"

PlayerStats::PlayerStats(BranchManager* bm, float x, float y)
{
	Branch::Branch(bm);
	manager = bm;
	timer.reset();
	frame = new Frame("stats.fram", x, y);
	init(false);
}

PlayerStats::PlayerStats(BranchManager* bm)
{
	Branch::Branch(bm);
	manager = bm;
	timer.reset();
	frame = new Frame("stats.fram", 10, -20);
	init(true);
}

PlayerStats::~PlayerStats()
{
}

void PlayerStats::init(bool animate)
{
	//PLAYER INFO
	Text* name = new Text(false, Character::player->getName(), false, 0, 0, 
		frame->getPosition().x + 2, frame->getPosition().y + 2);

	string str = "";
	if (Character::player->getRole() == Knight)
	{
		str = "Knight";
	}
	else if (Character::player->getRole() == Ranger)
	{
		str = "Ranger";
	}
	else
	{
		str = "Wizard";
	}
	Text* level = new Text(false, "<YELLOW>Lvl " + to_string(static_cast<long long>(Character::player->getLevel())) + " " + str, 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 7);

	//HP AND XP
	Text* hp = new Text(false, "HP ", false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 13);
	Text* xp = new Text(false, "XP ", false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 15);
	hpBar = new StatusBar(14, FG_WHITE, BG_RED, BG_DARKGRAY, frame->getPosition().x + 5, frame->getPosition().y + 13);
	xpBar = new StatusBar(14, FG_WHITE, BG_BROWN, BG_DARKGRAY, frame->getPosition().x + 5, frame->getPosition().y + 15);

	//BASE STATS
	Text* strength = new Text(false, "Str: " + to_string(static_cast<long long>(Character::player->getStats().strength)), 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 9);
	Text* dexterity = new Text(false, "Dex: " + to_string(static_cast<long long>(Character::player->getStats().dexterity)), 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 10);
	Text* intelligence = new Text(false, "Int: " + to_string(static_cast<long long>(Character::player->getStats().intelligence)), 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 11);

	//OFFENSE STATS
	Text* melee = new Text(false, "Melee: " + to_string(static_cast<long long>(Character::player->getStats().melee)), 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 7);
	Text* range = new Text(false, "Ranged: " + to_string(static_cast<long long>(Character::player->getStats().range)), 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 8);
	Text* magic = new Text(false, "Magic: " + to_string(static_cast<long long>(Character::player->getStats().magic)), 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 9);

	//DEFENSE STATS
	Text* armor = new Text(false, "Armor: " + to_string(static_cast<long long>(Character::player->getStats().armor)), 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 13);
	Text* dodge = new Text(false, "Dodge: " + to_string(static_cast<long long>(Character::player->getStats().dodge)) + "%", 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 14);
	Text* resist = new Text(false, "Resist: " + to_string(static_cast<long long>(Character::player->getStats().resist)), 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 15);

	//WEAPON
	Text* eq1Name = new Text(false, Character::player->getWeapon().getName(), 
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 5);
	Text* eq1Base = new Text(false, "Melee: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().melee)),
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 7);
	Text* eq1Atk = new Text(false, "Ranged: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().range)), 
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 8);
	Text* eq1Def = new Text(false, "Magic: " + to_string(static_cast<long long>(Character::player->getWeapon().getStats().magic)), 
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 9);

	//ARMOR
	Text* eq2Name = new Text(false, Character::player->getArmor().getName(), 
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 11);
	Text* eq2Base = new Text(false, "Armor: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().armor)), 
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 13);
	Text* eq2Atk = new Text(false, "Dodge: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().dodge)), 
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 14);
	Text* eq2Def = new Text(false, "Resist: " + to_string(static_cast<long long>(Character::player->getArmor().getStats().resist)), 
		false, 0, 0, frame->getPosition().x + 42, frame->getPosition().y + 15);

	Tween* tween = new Tween(SinOut, frame, 10, 3, 0.3f);
	tween->add(name);
	tween->add(level);
	tween->add(hp);
	tween->add(xp);
	tween->add(hpBar);
	tween->add(xpBar);
	tween->add(strength);
	tween->add(dexterity);
	tween->add(intelligence);
	tween->add(armor);
	tween->add(dodge);
	tween->add(resist);
	tween->add(melee);
	tween->add(range);
	tween->add(magic);
	tween->add(eq1Name);
	tween->add(eq1Base);
	tween->add(eq1Atk);
	tween->add(eq1Def);
	tween->add(eq2Name);
	tween->add(eq2Base);
	tween->add(eq2Atk);
	tween->add(eq2Def);
	tween->play();

	myFrames.push_back(frame);
	myFrames.push_back(name);
	myFrames.push_back(level);
	myFrames.push_back(hp);
	myFrames.push_back(xp);
	myFrames.push_back(hpBar);
	myFrames.push_back(xpBar);
	myFrames.push_back(strength);
	myFrames.push_back(dexterity);
	myFrames.push_back(intelligence);
	myFrames.push_back(armor);
	myFrames.push_back(dodge);
	myFrames.push_back(resist);
	myFrames.push_back(melee);
	myFrames.push_back(range);
	myFrames.push_back(magic);
	myFrames.push_back(eq1Name);
	myFrames.push_back(eq1Base);
	myFrames.push_back(eq1Atk);
	myFrames.push_back(eq1Def);
	myFrames.push_back(eq2Name);
	myFrames.push_back(eq2Base);
	myFrames.push_back(eq2Atk);
	myFrames.push_back(eq2Def);

	myTweens.push_back(tween);
}

void PlayerStats::update(float delta)
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

	string hpText = to_string(static_cast<long long>(Character::player->getStats().health))
		+ "/" + to_string(static_cast<long long>(Character::player->getHealth()));
	hpBar->calculateBar(hpText, Character::player->getStats().health, Character::player->getHealth());
	string xpText = to_string(static_cast<long long>(Character::player->getXP()))
		+ "/" + to_string(static_cast<long long>(Character::player->getXPToLevel()));
	xpBar->calculateBar(xpText, Character::player->getXP(), Character::player->getXPToLevel());
}

void PlayerStats::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void PlayerStats::start(float delta)
{
	if (Input::keyHit() && (Input::get() == 's' || Input::get() == 'p'))
	{
		state = End;
		myTweens.at(0)->restart(10, -22);
		myTweens.at(0)->setDuration(0.3f);
	}
	else if (Input::get() == 'i' || Input::get() == 'b')
	{
		manager->swap(new PlayerInventory(manager, frame->getPosition().x, frame->getPosition().y));
	}
}

void PlayerStats::input(float delta)
{
}

void PlayerStats::end(float delta)
{
	if (Input::keyHit() && (Input::get() == 's' || Input::get() == 'p'))
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