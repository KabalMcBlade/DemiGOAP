#pragma once

#include "Core.h"
#include "HashedString.h"
#include "WorldState.h"


DEMIGOAP_NAMESPACE_BEGIN

class Action final
{
public:
	Action(const HashedString& _hash, float _cost) : m_hash(_hash), m_cost(_cost) {}

	const std::string& GetName() const;
	const uint32_t GetID() const;

	void SetCost(float _cost);

	bool CanComputeOn(const WorldState& _worldState) const;

	WorldState Compute(const WorldState& _worldState) const;

	DEMIGOAP_INLINE void SetPrecondition(const HashedString& _name, const bool _value) { m_preconditions[_name] = _value; }
	DEMIGOAP_INLINE void SetEffect(const HashedString& _name, const bool _value) { m_effects[_name] = _value; }
	DEMIGOAP_INLINE float GetCost() const { return m_cost; }

private:
	HashedString m_hash;
	float m_cost;

	std::unordered_map<uint32_t, bool> m_preconditions;
	std::unordered_map<uint32_t, bool> m_effects;
};

DEMIGOAP_NAMESPACE_END
