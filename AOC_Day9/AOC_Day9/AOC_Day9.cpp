// AOC_Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

bool pairAdd(int preamble, std::vector<unsigned long long> numbers, unsigned long long answer) {
	auto start = numbers.size() - preamble;
	for (int i = start; i < numbers.size(); i++) {
		for (int j = start; j < numbers.size(); j++) {
			if (i == j) continue;
			if (numbers.at(i) + numbers.at(j) == answer) {
				return true;
			}
		}
	}
	return false;
}

int main()
{
	std::ifstream fileInput;
	fileInput.open("input.txt");
	auto preamble = 25;
	auto prevNumbers = 25;
	if (fileInput.is_open()) {
		std::string line = "";
		std::vector<unsigned long long> numbers;
		unsigned long long new_number;
		// get preamble numbers
		for (auto i = 0; i < preamble; i++) {
			getline(fileInput, line);
			new_number = std::stoull(line);
			numbers.push_back(new_number);
		}

		while (getline(fileInput, line)) {
			auto new_number = std::stoull(line);
			
			// check to see if any of the previous numbers add up
			if (pairAdd(preamble, numbers, new_number)) {
				numbers.push_back(new_number);
			}
			else {
				std::cout << "No pair found for " << new_number << std::endl;
				break;
			}

		}

		// find run of numbers that add up to this number

		// pairs already checked, so might as well go for threes
		auto runIndex = 0;
		auto finalAnswer = std::stoull(line);
		for (int i = 3; i < numbers.size(); ++i) {
			for (int j = 0; j <= numbers.size() - i; j++) {
				unsigned long long sum = 0;
				std::vector<unsigned long long> sum_numbers;

				for (int k = 0; k < i; k++) {
					sum_numbers.push_back(numbers.at(k + j));
				}
				sum = std::accumulate(sum_numbers.begin(), sum_numbers.end(), 0);
				if (sum == finalAnswer) {
					std::sort(sum_numbers.begin(), sum_numbers.end());
					std::cout << "Number run first and last " << *sum_numbers.begin() + *--sum_numbers.end() << std::endl;
					return 0;
				}
			}
		}
		std::cout << "No run of numbers found" << std::endl;
		fileInput.close();
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
