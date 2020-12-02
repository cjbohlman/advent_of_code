// AOC_Day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdbool.h>

void printVector(std::vector<int> const &nums) {
	for (int i = 0; i < nums.size(); i++) {
		std::cout << nums.at(i) << std::endl;
	}
}

bool findSumNums(std::vector<int> const &nums, const int & missingNo, int & n1, int & n2) {
	for (auto i = 0; i < nums.size(); ++i) {
		auto difference = missingNo - nums.at(i);
		if (std::binary_search(std::next(nums.begin(), i), nums.end(), difference)) {
			n1 = nums.at(i);
			n2 = difference;
			return true;
		}
	}
	return false;
}

void findMissingNo(std::vector<int>& nums, const int & sum) {
		for (auto i = 0; i < nums.size(); ++i) {
			auto missingNo = sum - nums.at(i);
			// find two numbers that sum to missingNo
			auto n1 = 0, n2 = 0;
			if (findSumNums(nums, missingNo, n1, n2)) {
				std::cout << "Result: " << nums.at(i) << " * " << n1 << " * " << n2 << " = " << n1 * n2 * nums.at(i) << std::endl;
				return;
			}

		}
		std::cout << "Nothing found..." << std::endl;
		return;
	}

	int main() {
		std::ifstream fileInput;
		fileInput.open("input.txt");
		if (fileInput.is_open()) {
			std::string line = "";
			std::vector<int> nums;
			const int sum = 2020;
			while (getline(fileInput, line)) {
				nums.push_back(std::stoi(line));
			}
			printVector(nums);

			std::sort(nums.begin(), nums.end());

			findMissingNo(nums, sum);

			fileInput.close();
		}
		else {
			std::cerr << "Error opening input file" << std::endl;
		}
	}