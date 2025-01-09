// Copyright (c) 2020-2025 Michele Condo'
// File: C:\Projects\DemiGOAP\DemiGOAP\DemiGOAP\PlanNode.cpp
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
#include "PlanNode.h"
#include "PlanRequest.h"
#include "Action.h"

DEMIGOAP_NAMESPACE_BEGIN

const uint32_t PlanNode::GetID() const
{
	if (m_actionLedHere == nullptr)
	{
		return m_currentWorldState.GetID();
	}
	return m_actionLedHere->GetID();
}

const std::string& PlanNode::GetName() const
{
	if (m_actionLedHere == nullptr)
	{
		return m_currentWorldState.GetName();
	}
	return m_actionLedHere->GetName();
}

bool PlanNode::operator==(const PlanNode& _rhs) const
{
	return m_currentWorldState.EqualTo(_rhs.GetCurrentWorldState());
}

int32_t PlanNode::FindIndexInOpenList(const std::vector<PlanNode>& _list) const
{
	auto it = std::find_if(std::begin(_list), std::end(_list), [&](const PlanNode & n) { return n.GetCurrentWorldState().EqualTo(GetCurrentWorldState()); });
	int32_t index = static_cast<int32_t>(std::distance(_list.begin(), it));
	return index;
}

bool PlanNode::IsInClosedList(const std::vector<PlanNode>& _list) const
{
	if (std::find_if(begin(_list), end(_list), [&](const PlanNode & n) { return n.GetCurrentWorldState().EqualTo(GetCurrentWorldState()); }) == end(_list)) 
	{
		return false;
	}
	return true;
}

void PlanNode::GetNeighbors(const PlanRequest& _request, std::vector<PlanNode>& _neighbors) const
{
	for (const auto& action : _request.GetActions())
	{
		if (action.CanComputeOn(m_currentWorldState))
		{
			WorldState newWorldState = action.Compute(GetCurrentWorldState());
			PlanNode newNode(newWorldState, &action);
			_neighbors.push_back(newNode);
		}
	}
}

bool PlanNode::IsGoal(const PlanRequest& _request, const PlanNode& _otherNode) const
{
	return m_currentWorldState.IsGoal(_otherNode.GetCurrentWorldState());
}

float PlanNode::ComputeCost(const PlanRequest& _request, const PlanNode& _otherNode) const
{
	float cost = m_actionLedHere != nullptr ? m_actionLedHere->GetCost() : 0.0f;
		
	for (const auto& action : _request.GetActions())
	{
		if (_otherNode.GetActionLedHere() == &action && action.CanComputeOn(_otherNode.GetCurrentWorldState()))
		{
			cost += action.GetCost();
		}
	}

	return cost;
}

float PlanNode::EstimateCost(const PlanRequest& _request, const PlanNode& _otherNode) const
{
	return m_currentWorldState.Distance(_otherNode.GetCurrentWorldState());
}

DEMIGOAP_NAMESPACE_END