#pragma once

#include "../DemiGOAP/DemiGOAP.h"


class Weaponsmith
{
public:
	Weaponsmith(const std::string& _name);
	~Weaponsmith();

	void Update();

private:
	void Simulate(uint32_t _id, const std::string& _name);

private:
	std::string m_name;
	DemiGOAP::PlanRequest m_request;
	DemiGOAP::AStar<DemiGOAP::PlanRequest> m_plan;
};

