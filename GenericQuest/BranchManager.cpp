#include "stdafx.h"
#include "Canvas.h"
#include "Branch.h"
#include "BranchManager.h"

BranchManager::BranchManager()
{
}

BranchManager::BranchManager(Branch* branch)
{
	branches.push_back(branch);
}

BranchManager::~BranchManager()
{
}

void BranchManager::update(float delta)
{
	for (int i = 0; i < branches.size(); i++)
	{
		branches.at(i)->update(delta);
	}
}

void BranchManager::draw(Canvas* canvas)
{
	for (int i = 0; i < branches.size(); i++)
	{
		branches.at(i)->draw(canvas);
	}
}

void BranchManager::swap(Branch* newBranch)
{
	branches.clear();
	branches.push_back(newBranch);
}

void BranchManager::add(Branch* newBranch)
{
	branches.push_back(newBranch);
}