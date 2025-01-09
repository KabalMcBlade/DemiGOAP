// Copyright (c) 2020-2025 Michele Condo'
// File: C:\Projects\DemiGOAP\DemiGOAP\DemiGOAP\WorldState.cpp
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
#include "WorldState.h"


DEMIGOAP_NAMESPACE_BEGIN

bool WorldState::Exist(const uint32_t _id) const
{
	return m_data.count(_id) > 0;
}

bool WorldState::IsGoal(const WorldState& _other) const
{
	for (const auto& kv : _other.GetData())
	{
		if (!Exist(kv.first) || (Exist(kv.first) && GetValue(kv.first) != kv.second))
		{
			return false;
		}
	}
	return true;
}

float WorldState::Distance(const WorldState& _other) const
{
	float cost = 0.0f;

	for (const auto& kv : _other.GetData())
	{
		auto it = GetData().find(kv.first);
		if (it == std::end(GetData()) || it->second != kv.second)
		{
			cost += 1.0f;
		}
	}

	return cost;
}

DEMIGOAP_NAMESPACE_END
