// AOC_Day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>

auto getBoardingPassRow(std::string boardingPass) {
	auto rangeMin = 0;
	auto rangeMax = 127;
	for (auto i = 0; i < 7; i++) {
		int halfway = (rangeMax + rangeMin)/2;
		if (boardingPass.at(i) == 'F') {
			rangeMax = halfway;
		} else if (boardingPass.at(i) == 'B') {
			rangeMin = halfway + 1;
		}
		else {
			std::cerr << "Incorrect char found in boarding pass row" << std::endl;
		}
	}
	if(rangeMin == rangeMax) {
		return rangeMin;
	}
	else {
		std::cerr << "row not found" << std::endl;
		return 0;
	}
}

auto getBoardingPassCol(std::string boardingPass) {
	auto rangeMin = 0;
	auto rangeMax = 7;
	for (auto i = 7; i < 10; i++) {
		int halfway = (rangeMax + rangeMin) / 2;
		if (boardingPass.at(i) == 'L') {
			rangeMax = halfway;
		}
		else if (boardingPass.at(i) == 'R') {
			rangeMin = halfway + 1;
		}
		else {
			std::cerr << "Incorrect char found in boarding pass col" << std::endl;
		}
	}
	if (rangeMin == rangeMax) {
		return rangeMin;
	}
	else {
		std::cerr << "col not found" << std::endl;
		return 0;
	}
}


auto getBoardingPassId(std::string boardingPass) {
	auto row = getBoardingPassRow(boardingPass);
	auto col = getBoardingPassCol(boardingPass);
	return row*8 + col;
}

int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	if (fileInput.is_open()) {
		std::string line = "";
		auto maxBoardingPassId = 0;
		std::vector<int> boardingPassIds;
		while (getline(fileInput, line)) {
			int boardingPassId = getBoardingPassId(line);
			if (boardingPassId > maxBoardingPassId) {
				maxBoardingPassId = boardingPassId;
			}
			boardingPassIds.push_back(boardingPassId);
		}
		std::cout << "Max passport ID: " << maxBoardingPassId << std::endl;
		std::sort(boardingPassIds.begin(), boardingPassIds.end());
		for (auto i = 0; i < boardingPassIds.size() - 1; i++) {
			if (boardingPassIds.at(i + 1) - boardingPassIds.at(i) == 2) {
				std::cout << "Your seat is " << boardingPassIds.at(i) + 1 << std::endl;
				return 0;
			}
		}
	}
	return 0;
}