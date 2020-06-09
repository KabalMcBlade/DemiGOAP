#pragma once

#include "Core.h"
#include "HashedString.h"


DEMIGOAP_NAMESPACE_BEGIN

static const HashedString kNoNameHash("##NO_NAME##");

class WorldState final
{
public:
	WorldState() : m_hash(kNoNameHash) {}
	WorldState(const HashedString& _hash) : m_hash(_hash) { }
	WorldState(const WorldState& _other) : m_hash(_other.m_hash), m_data(_other.m_data) { }

	bool Exist(const uint32_t _id) const;
	bool IsGoal(const WorldState& _other) const;
	float Distance(const WorldState& _other) const;

	DEMIGOAP_INLINE void SetName(const HashedString& _name)
	{
		m_hash = _name;
	}

	DEMIGOAP_INLINE const std::string& GetName() const
	{
		return m_hash;
	}

	DEMIGOAP_INLINE uint32_t GetID() const
	{
		return m_hash;
	}

	DEMIGOAP_INLINE bool GetValue(const uint32_t _id) const
	{
		return m_data.at(_id);
	}

	DEMIGOAP_INLINE void SetData(const uint32_t _id, const bool _value)
	{
		m_data[_id] = _value;
	}

	DEMIGOAP_INLINE const std::map<uint32_t, bool>& GetData() const { return m_data; }

	DEMIGOAP_INLINE bool EqualTo(const WorldState& _other) const
	{
		return m_data == _other.GetData();
	}

private:
	HashedString m_hash;
	std::map<uint32_t, bool> m_data;
};


DEMIGOAP_NAMESPACE_END
