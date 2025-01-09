// Copyright (c) 2020-2025 Michele Condo'
// File: C:\Projects\DemiGOAP\DemiGOAP\Test\Weaponsmith.cpp
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
#include "Weaponsmith.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <random>


namespace WeaponsmithDefines
{
	// define actions
	static const DemiGOAP::HashedString ACTION_ChopTree("Chop Tree");
	static const DemiGOAP::HashedString ACTION_MineOre("Mine Ore");
	static const DemiGOAP::HashedString ACTION_SmeltOre("Smelt Ore");
	static const DemiGOAP::HashedString ACTION_WorksWood("Works Wood");
	static const DemiGOAP::HashedString ACTION_CreateAxe("Create Axe");
	static const DemiGOAP::HashedString ACTION_SellAxe("Sell Axe");
	static const DemiGOAP::HashedString ACTION_StealGold("Steal Gold");

	// define preconditions and effects
	static const DemiGOAP::HashedString STATE_HasRawWood("Has Raw Wood");
	static const DemiGOAP::HashedString STATE_HasOre("Has Ore");
	static const DemiGOAP::HashedString STATE_HasIron("Has Iron");
	static const DemiGOAP::HashedString STATE_HasWood("Has Wood");
	static const DemiGOAP::HashedString STATE_HasAxe("Has Axe");
	static const DemiGOAP::HashedString STATE_HasGold("Has Gold");

	// define name of the initial world states
	static const DemiGOAP::HashedString kBeginWorldStateId("No Gold");
	static const DemiGOAP::HashedString kEndWorldStateId("Has Gold");
}


Weaponsmith::Weaponsmith(const std::string& _name) : m_name(_name)
{
	// create actions
	DemiGOAP::Action chopTree(WeaponsmithDefines::ACTION_ChopTree, 1.0f);
	chopTree.SetEffect(WeaponsmithDefines::STATE_HasRawWood, true);
	chopTree.SetPrecondition(WeaponsmithDefines::STATE_HasRawWood, false);
	chopTree.SetPrecondition(WeaponsmithDefines::STATE_HasWood, false);

	DemiGOAP::Action mineOre(WeaponsmithDefines::ACTION_MineOre, 1.0f);
	mineOre.SetEffect(WeaponsmithDefines::STATE_HasOre, true);
	mineOre.SetPrecondition(WeaponsmithDefines::STATE_HasOre, false);
	mineOre.SetPrecondition(WeaponsmithDefines::STATE_HasIron, false);

	DemiGOAP::Action smeltOre(WeaponsmithDefines::ACTION_SmeltOre, 1.0f);
	smeltOre.SetEffect(WeaponsmithDefines::STATE_HasIron, true);
	smeltOre.SetEffect(WeaponsmithDefines::STATE_HasOre, false);
	smeltOre.SetPrecondition(WeaponsmithDefines::STATE_HasOre, true);

	DemiGOAP::Action worksWood(WeaponsmithDefines::ACTION_WorksWood, 1.0f);
	worksWood.SetEffect(WeaponsmithDefines::STATE_HasWood, true);
	worksWood.SetEffect(WeaponsmithDefines::STATE_HasRawWood, false);
	worksWood.SetPrecondition(WeaponsmithDefines::STATE_HasRawWood, true);

	DemiGOAP::Action createAxe(WeaponsmithDefines::ACTION_CreateAxe, 3.0f);
	createAxe.SetEffect(WeaponsmithDefines::STATE_HasAxe, true);
	createAxe.SetEffect(WeaponsmithDefines::STATE_HasWood, false);
	createAxe.SetEffect(WeaponsmithDefines::STATE_HasIron, false);
	createAxe.SetPrecondition(WeaponsmithDefines::STATE_HasWood, true);
	createAxe.SetPrecondition(WeaponsmithDefines::STATE_HasIron, true);

	DemiGOAP::Action sellAxe(WeaponsmithDefines::ACTION_SellAxe, 3.0f);
	sellAxe.SetEffect(WeaponsmithDefines::STATE_HasGold, true);
	sellAxe.SetEffect(WeaponsmithDefines::STATE_HasAxe, false);
	sellAxe.SetPrecondition(WeaponsmithDefines::STATE_HasAxe, true);

	DemiGOAP::Action stealGold(WeaponsmithDefines::ACTION_StealGold, 20.0f);
	stealGold.SetEffect(WeaponsmithDefines::STATE_HasGold, true);
	stealGold.SetPrecondition(WeaponsmithDefines::STATE_HasAxe, false);
	stealGold.SetPrecondition(WeaponsmithDefines::STATE_HasIron, false);
	stealGold.SetPrecondition(WeaponsmithDefines::STATE_HasWood, false);
	stealGold.SetPrecondition(WeaponsmithDefines::STATE_HasRawWood, false);
	stealGold.SetPrecondition(WeaponsmithDefines::STATE_HasOre, false);
	

	// creates initial and goal states
	DemiGOAP::WorldState initialState(WeaponsmithDefines::kBeginWorldStateId);
	initialState.SetData(WeaponsmithDefines::STATE_HasGold, false);
	initialState.SetData(WeaponsmithDefines::STATE_HasAxe, false);
	initialState.SetData(WeaponsmithDefines::STATE_HasIron, false);
	initialState.SetData(WeaponsmithDefines::STATE_HasWood, false);
	initialState.SetData(WeaponsmithDefines::STATE_HasRawWood, false);
	initialState.SetData(WeaponsmithDefines::STATE_HasOre, false);

	DemiGOAP::WorldState goalState(WeaponsmithDefines::kEndWorldStateId);
	goalState.SetData(WeaponsmithDefines::STATE_HasGold, true);

	// fill the nodes with the world states
	DemiGOAP::PlanNode worldInitState(initialState);
	DemiGOAP::PlanNode worldGoalState(goalState);

	// fill the request
	m_request.AddAction(chopTree);
	m_request.AddAction(mineOre);
	m_request.AddAction(smeltOre);
	m_request.AddAction(worksWood);
	m_request.AddAction(createAxe);
	m_request.AddAction(sellAxe);
	m_request.AddAction(stealGold);

	m_request.SetNodes(worldInitState, worldGoalState);
}

Weaponsmith::~Weaponsmith()
{
}

void Weaponsmith::Update()
{
	float totalCost = 0.0;

	m_plan.Search(m_request);

	if (m_plan.IsSearchCompleted())
	{
		if (m_plan.GetResultState() == DemiGOAP::AStar<DemiGOAP::PlanRequest>::EAStarResult_Pathfound)
		{
			DemiGOAP::AStar<DemiGOAP::PlanRequest>::Solution solution = m_plan.GetSolution();
			for (DemiGOAP::AStar<DemiGOAP::PlanRequest>::Solution::iterator it = solution.begin(); it != solution.end(); ++it)
			{
				Simulate((*it).GetID(), (*it).GetName());
			}
		}
		else
		{
			std::cout << "No solution found" << std::endl;
		}
	}
	else
	{
		std::cout << "The planner was unable to complete. Error: " << m_plan.GetResultState() << std::endl;
	}
}

void Weaponsmith::Simulate(uint32_t _id, const std::string& _name)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.1f, 1.0f);
	std::uniform_int_distribution<uint32_t> acts(1, 6);

	const bool bHasActionInterrupted = dist(mt) > 0.499f;

	const bool bIsInAnyOfTheseAction =
		_id == WeaponsmithDefines::ACTION_ChopTree ||
		_id == WeaponsmithDefines::ACTION_MineOre ||
		_id == WeaponsmithDefines::ACTION_SmeltOre ||
		_id == WeaponsmithDefines::ACTION_WorksWood ||
		_id == WeaponsmithDefines::ACTION_CreateAxe ||
		_id == WeaponsmithDefines::ACTION_SellAxe;
	
	std::cout << _name;
	
	if (bIsInAnyOfTheseAction && bHasActionInterrupted)
	{
		const float increasesCost = dist(mt);

		DemiGOAP::Action* action = m_request.GetAction(_id);
		if (action)
		{
			const float newCost = action->GetCost() + increasesCost;
			action->SetCost(newCost);
		}

		std::cout << " <- COST INCREASED BY " << increasesCost;
	}
	
	if (_id == WeaponsmithDefines::ACTION_StealGold)
	{
		const uint32_t actionCount = acts(mt);

		static 	const uint32_t actionList[] = { 
			WeaponsmithDefines::ACTION_ChopTree, 
			WeaponsmithDefines::ACTION_MineOre, 
			WeaponsmithDefines::ACTION_SmeltOre,
			WeaponsmithDefines::ACTION_WorksWood,
			WeaponsmithDefines::ACTION_CreateAxe,
			WeaponsmithDefines::ACTION_SellAxe
		};

		float totalCostDecreasedBy = 0.0f;

		std::cout << " - [";
		for (uint32_t i = 0; i < actionCount; ++i)
		{
			DemiGOAP::Action* action = m_request.GetAction(actionList[i]);

			if (action)
			{
				const float decreasesCost = dist(mt);
				const float newCost = action->GetCost() - decreasesCost;
				action->SetCost(newCost);

				totalCostDecreasedBy += decreasesCost;
				
				std::cout << action->GetName();
			}

			if (i < actionCount - 1)
			{
				std::cout << ", ";
			}
		}

		std::cout << "] -> COST DECREASED FOR A TOTAL OF " << totalCostDecreasedBy;
	}
	
	std::cout << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}