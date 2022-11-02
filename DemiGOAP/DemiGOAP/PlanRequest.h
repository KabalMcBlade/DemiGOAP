#pragma once

#include "Core.h"
#include "PlanNode.h"
#include "Action.h"


DEMIGOAP_NAMESPACE_BEGIN

class HashedString;
class PlanRequest final
{
public:
	typedef PlanNode Node;

	static constexpr uint32_t kAStarMaxResultList = 5000;
	static constexpr uint32_t kAStarMaxOpentList = 10000;

	PlanRequest() {}

	// the _id can be the HashedString, since has the convert operator!
	const Action* GetAction(const uint32_t _id) const;
	Action* GetAction(const uint32_t _id);

	void AddAction(const Action& _action);
	void SetNodes(const Node& _start, const Node& _end);
	float GetMaxPathCost() const;

	DEMIGOAP_INLINE const std::vector<Action>& GetActions() const { return m_actions; }
	DEMIGOAP_INLINE const Node& GetStartNode() const { return m_startNode; }
	DEMIGOAP_INLINE const Node& GetEndNode() const { return m_endNode; }

	// update purpose only
	DEMIGOAP_INLINE Node& GetStartNode() { return m_startNode; }
	DEMIGOAP_INLINE Node& GetEndNode() { return m_endNode; }

private:
	Node m_startNode;
	Node m_endNode;

	std::vector<Action> m_actions;
};

DEMIGOAP_NAMESPACE_END
