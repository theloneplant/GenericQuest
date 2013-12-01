#include "stdafx.h"
#include "Canvas.h"
#include "Input.h"
#include "Branch.h"
#include "PlayerStats.h"
#include "PlayerInventory.h"
#include "BranchManager.h"

BranchManager::BranchManager()
{
	gameStarted = false;
	inMenu = false;
}

BranchManager::BranchManager(Branch* branch)
{
	gameStarted = false;
	inMenu = false;
	branches.push_back(branch);
}

BranchManager::~BranchManager()
{
}

void BranchManager::update(float delta)
{
	branches.at(branches.size() - 1)->update(delta);

	if (gameStarted && Input::keyHit())
	{
		char input = Input::get();
		if (input == 's' || input == 'p')
		{
			if (!inMenu)
			{
				PlayerStats* stats = new PlayerStats(this);
				push(stats);
				inMenu = true;
			}
		}
		else if (input == 'i' || input == 'b')
		{
			if (!inMenu)
			{
				PlayerInventory* stats = new PlayerInventory(this);
				push(stats);
				inMenu = true;
			}
		}
		else if (input == 27)
		{
			_CrtDumpMemoryLeaks();
			exit(EXIT_SUCCESS);
		}
	}
}

void BranchManager::draw(Canvas* canvas)
{
	for (unsigned int i = 0; i < branches.size(); i++)
	{
		branches.at(i)->draw(canvas);
	}
}

void BranchManager::swap(Branch* newBranch)
{
	branches.pop_back();
	branches.push_back(newBranch);
}

void BranchManager::push(Branch* newBranch)
{
	branches.push_back(newBranch);
}

void BranchManager::pop()
{
	branches.pop_back();
}

void BranchManager::setGameStart(bool started)
{
	gameStarted = started;
}

void BranchManager::setInMenu(bool newInMenu)
{
	inMenu = newInMenu;
}