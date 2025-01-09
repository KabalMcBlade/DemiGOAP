// Copyright (c) 2020-2025 Michele Condo'
// File: C:\Projects\DemiGOAP\DemiGOAP\DemiGOAP\Action.cpp
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
#include "Action.h"


DEMIGOAP_NAMESPACE_BEGIN

const std::string& Action::GetName() const
{
	return m_hash;
}

const uint32_t Action::GetID() const
{
	return m_hash;
}

void Action::SetCost(float _cost)
{
	m_cost = _cost;
}

bool Action::CanComputeOn(const WorldState& _worldState) const
{
	for (std::pair<uint32_t, bool> it : m_preconditions)
	{
		if (!_worldState.Exist(it.first) || (_worldState.Exist(it.first) && _worldState.GetValue(it.first) != it.second))
		{
			return false;
		}
	}

	return true;
}

WorldState Action::Compute(const WorldState& _worldState) const
{
	WorldState tmp(_worldState);
	for (const auto& effect : m_effects)
	{
		tmp.SetData(effect.first, effect.second);
	}
	return tmp;
}

DEMIGOAP_NAMESPACE_END
