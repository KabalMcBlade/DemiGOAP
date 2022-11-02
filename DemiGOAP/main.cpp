// NanoGOAP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#include <winsock.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <random>

#include "Test/Weaponsmith.h"


int main()
{
	int32_t count = 0;

	std::cout << "How many iteration?" << std::endl;
	std::cin >> count;

	Weaponsmith weaponsmith("Dude");

	std::cout << std::endl << "START ITERATIONS" << std::endl << std::endl;

	while (count > 0)
	{
		weaponsmith.Update();

		--count;

		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	std::cout << std::endl << "END ITERATIONS" << std::endl;
}