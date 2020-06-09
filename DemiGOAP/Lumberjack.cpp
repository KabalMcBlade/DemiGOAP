#include "Lumberjack.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <random>


namespace LumberjackStates
{
	// define name of the world states
	static const DemiGOAP::HashedString kBeginWorldStateId("NoAxeNorWoods");
	static const DemiGOAP::HashedString kEndWorldStateId("HasWoods");

	// define actions
	static const DemiGOAP::HashedString kGetAxeId("GetAxe");
	static const DemiGOAP::HashedString kChopLogsId("ChopLogs");
	static const DemiGOAP::HashedString kCollectBranchesId("CollectBranches");
	
	// define states
	static const DemiGOAP::HashedString kHasAxeId("HasAxe");
	static const DemiGOAP::HashedString kHasWoodId("HasWood");
}


Lumberjack::Lumberjack(const std::string& _name) : m_name(_name)
{
	// create some actions
	DemiGOAP::Action getAxe(LumberjackStates::kGetAxeId, 1.0f);
	getAxe.SetEffect(LumberjackStates::kHasAxeId, true);

	DemiGOAP::Action chopLogs(LumberjackStates::kChopLogsId, 4.0f);
	chopLogs.SetPrecondition(LumberjackStates::kHasAxeId, true);
	chopLogs.SetEffect(LumberjackStates::kHasWoodId, true);

	DemiGOAP::Action collectBranches(LumberjackStates::kCollectBranchesId, 7.0f);
	collectBranches.SetEffect(LumberjackStates::kHasWoodId, true);


	// creates initial and goal states
	DemiGOAP::WorldState initialState(LumberjackStates::kBeginWorldStateId);
	initialState.SetData(LumberjackStates::kHasAxeId, false);
	initialState.SetData(LumberjackStates::kHasWoodId, false);

	DemiGOAP::WorldState goalState(LumberjackStates::kEndWorldStateId);
	goalState.SetData(LumberjackStates::kHasWoodId, true);

	// fill the nodes with the world states
	DemiGOAP::PlanNode worldInitState(initialState);
	DemiGOAP::PlanNode worldGoalState(goalState);

	// fill the request
	m_request.AddAction(getAxe);
	m_request.AddAction(chopLogs);
	m_request.AddAction(collectBranches);
	m_request.SetNodes(worldInitState, worldGoalState);

	m_foundAxe = false;
	m_durationAxe = 1.0f;
}

Lumberjack::~Lumberjack()
{
}

void Lumberjack::Update()
{
	//////////////////////////////////////////////////////////////////////////
	// add oddities
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0f, 5.0f);

	m_request.GetStartNode().GetCurrentWorldState().SetData(LumberjackStates::kHasAxeId, m_foundAxe);

	DemiGOAP::Action* action = m_request.GetAction(LumberjackStates::kGetAxeId);
	if (action)
	{
		action->SetCost(dist(mt));
	}
	//////////////////////////////////////////////////////////////////////////


	m_plan.Search(m_request);

	if (m_plan.IsSearchCompleted())
	{
		if (m_plan.GetResultState() == DemiGOAP::AStar<DemiGOAP::PlanRequest>::EAStarResult_Pathfound)
		{
			DemiGOAP::AStar<DemiGOAP::PlanRequest>::Solution solution = m_plan.GetSolution();
			for (DemiGOAP::AStar<DemiGOAP::PlanRequest>::Solution::iterator it = solution.begin(); it != solution.end(); ++it)
			{
				Simulate((*it).GetID());
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

void Lumberjack::Simulate(uint32_t _id)
{
	if (_id == LumberjackStates::kBeginWorldStateId)
	{
		std::cout << m_name << " begin is working day." << std::endl;
	}
	else if (_id == LumberjackStates::kGetAxeId)
	{
		std::cout << m_name << " found an axe and get it." << std::endl;
		m_foundAxe = true;
		m_durationAxe = 1.0f;
	}
	else if (_id == LumberjackStates::kChopLogsId)
	{
		std::cout << m_name << " with the axe he chops some logs." << std::endl;
	}
	else if (_id == LumberjackStates::kCollectBranchesId)
	{
		std::cout << m_name << " didn't find any axe to use, so go to collect some branches." << std::endl;
	}
	else if (_id == LumberjackStates::kEndWorldStateId)
	{
		std::random_device rd;
		std::mt19937 mt(rd());

		if (m_foundAxe)
		{
			std::uniform_real_distribution<float> dist(0.1f, 1.0f);
			m_durationAxe -= dist(mt);

			if (m_durationAxe < 0.01f)
			{
				std::cout << "* The axe is broken! *" << std::endl;
				m_foundAxe = false;
			}
		}

		std::cout << m_name << " finished the job." << std::endl;
	}
	else
	{
		std::cout << m_name << " does not know how to do!" << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(800));
}


#ifdef _DEBUG
void Lumberjack::Print()
{
	if (m_plan.IsSearchCompleted())
	{
		if (m_plan.GetResultState() == DemiGOAP::AStar<DemiGOAP::PlanRequest>::EAStarResult_Pathfound)
		{
			DemiGOAP::AStar<DemiGOAP::PlanRequest>::Solution solution = m_plan.GetSolution();

			for (DemiGOAP::AStar<DemiGOAP::PlanRequest>::Solution::iterator it = solution.begin(); it != solution.end(); ++it)
			{
				std::cout << "[" << (*it).GetID() << "]\t" << (*it).GetName() << std::endl;
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
#endif