// AOC_Day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "AOC_Day13.h"

void GetClosestTime(std::vector<int> &buses, int time)
{
	std::vector<int> results{};
	
	for (auto num : buses) {
		int acc = 0;
		while (acc < time) {
			acc += num;
		}
		results.push_back(acc - time);
	}

	auto closestBus = time;
	auto closestIndex = buses.size();
	for (int i = 0; i < results.size(); i++) {
		if (results.at(i) < closestBus) {
			closestBus = results.at(i);
			closestIndex = i;
		}
	}
	std::cout << "Closest bus id: " << buses.at(closestIndex) << " with value: " << buses.at(closestIndex)  * results.at(closestIndex) << std::endl;
}

void GetBusRun(std::vector<unsigned long long> buses)
{
	//auto t{ 100000000000001 };
	unsigned long long t = 100000000000001LL;
	auto run{true};
	auto min = buses.at(0);

	std::vector<int> busesFiltered{};
	std::vector<int> rems{};
	for (auto i{ 0 }; i < buses.size(); i++) {
		if (buses.at(i) != 0) {
			busesFiltered.push_back(buses.at(i));
			rems.push_back(i);
		}
	}

	while (run & t > 0) {
		bool loopChanged{ false };
		for (auto i{ 1 }; i < busesFiltered.size(); i++) {
			if (t % busesFiltered.at(i) != rems.at(i)) {
				loopChanged = true;
				break;
			}
		}

		if (loopChanged == false) {
			run = false;
		}
		t = t + min;
	}
	std::cout << "Bus run occurs at time: " << t - min << std::endl;
}

int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	// pair operates on an xy gird
	std::string time{};
	std::vector<int> busesNoX{};
	std::vector<unsigned long long> busesX;
	if (fileInput.is_open()) {
		std::string line = {};
		// get time
		getline(fileInput, line);
		auto time = std::stoi(line);

		while (getline(fileInput, line, ',')) {
			//get comma delimited bus id list
			if (line == "x") {
				busesX.push_back(0);
				continue;
			}
			busesNoX.push_back(std::stoi(line));
			busesX.push_back(std::stoull(line));
		}

		GetClosestTime(busesNoX, time);
		GetBusRun(busesX);
		fileInput.close();
	}
	return 0;
}