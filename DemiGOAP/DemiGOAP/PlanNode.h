#pragma once

#include "Core.h"
#include "HashedString.h"

#include "WorldState.h"


DEMIGOAP_NAMESPACE_BEGIN

class PlanRequest;
class Action;
class PlanNode
{
public:
	PlanNode() : m_actionLedHere(nullptr) {}
	PlanNode(const WorldState& _worldState, const Action* _action = nullptr) : m_currentWorldState(_worldState), m_actionLedHere(_action) {}
	~PlanNode() {}

	//////////////////////////////////////////////////////////////////////////
	// Required by A*
	int32_t FindIndexInOpenList(const std::vector<PlanNode>& _list) const;
	bool IsInClosedList(const std::vector<PlanNode>&) const;
	void GetNeighbors(const PlanRequest& _request, std::vector<PlanNode>& _neighbors) const;
	bool IsGoal(const PlanRequest& _request, const PlanNode& _otherNode) const;
	float ComputeCost(const PlanRequest& _request, const PlanNode& _otherNode) const;
	float EstimateCost(const PlanRequest& _request, const PlanNode& _otherNode) const;
	//////////////////////////////////////////////////////////////////////////

	const uint32_t GetID() const;
	const std::string& GetName() const;
	bool operator==(const PlanNode& _rhs) const;

	DEMIGOAP_INLINE void SetCurrentWorldState(const WorldState& _worldState) { m_currentWorldState = _worldState;}
	DEMIGOAP_INLINE void SetActionLedHere(const Action* _action) { m_actionLedHere = _action; }
	DEMIGOAP_INLINE const WorldState& GetCurrentWorldState() const { return m_currentWorldState; }
	DEMIGOAP_INLINE const Action* GetActionLedHere() const { return m_actionLedHere; }

	// Update purpose only
	DEMIGOAP_INLINE WorldState& GetCurrentWorldState() { return m_currentWorldState; }
	DEMIGOAP_INLINE Action* GetActionLedHere() { return const_cast<Action*>(m_actionLedHere); }

private:
	const Action* m_actionLedHere;
	WorldState m_currentWorldState;
};

DEMIGOAP_NAMESPACE_END