// NanoGOAP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

#include <winsock.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <random>

#include "Lumberjack.h"


int main()
{
	int32_t count = 0;
	std::string lumberName;

	std::cout << "How many iteration do you want for the lumberman?" << std::endl;
	std::cin >> count;

	std::cout << "What is the name of the lumberman?" << std::endl;
	std::cin >> lumberName;

	Lumberjack lumberjack(lumberName);

	std::cout << std::endl << "START ITERATIONS" << std::endl << std::endl;

	while (count > 0)
	{
		lumberjack.Update();

		--count;

		std::cout << std::endl << "Another day past" << std::endl << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}

	std::cout << std::endl << "END ITERATIONS" << std::endl;
}