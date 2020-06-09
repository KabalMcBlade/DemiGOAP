#pragma once

#include "DemiGOAP/DemiGOAP.h"


class Lumberjack
{
public:
	Lumberjack(const std::string& _name);
	~Lumberjack();

	void Update();

#ifdef _DEBUG
	void Print();
#endif

private:
	void Simulate(uint32_t _id);

private:
	std::string m_name;
	DemiGOAP::PlanRequest m_request;
	DemiGOAP::AStar<DemiGOAP::PlanRequest> m_plan;
	float m_durationAxe;
	bool m_foundAxe;
};

