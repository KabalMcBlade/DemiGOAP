// Copyright (c) 2020-2025 Michele Condo'
// File: C:\Projects\DemiGOAP\DemiGOAP\Test\Weaponsmith.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
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

