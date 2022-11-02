#include "PlanRequest.h"


DEMIGOAP_NAMESPACE_BEGIN

const Action* PlanRequest::GetAction(const uint32_t _id) const
{
	auto it = std::find_if(std::begin(m_actions), std::end(m_actions), [&](const Action& n) { return n.GetID() == _id; });

	if (it == std::end(m_actions))
	{
		return nullptr;
	}
	else
	{
		return &(*it);
	}
}

Action* PlanRequest::GetAction(const uint32_t _id)
{
	auto it = std::find_if(std::begin(m_actions), std::end(m_actions), [&](const Action& n) { return n.GetID() == _id; });

	if (it == std::end(m_actions))
	{
		return nullptr;
	}
	else
	{
		return &(*it);
	}
}

void PlanRequest::AddAction(const Action& _action)
{
	m_actions.push_back(_action);
}

void PlanRequest::SetNodes(const Node& _start, const Node& _end)
{
	m_startNode = _start;
	m_endNode = _end;
}

float PlanRequest::GetMaxPathCost() const
{
	// is possible put some linear constraint here
	return FLT_MAX;
}

DEMIGOAP_NAMESPACE_END
